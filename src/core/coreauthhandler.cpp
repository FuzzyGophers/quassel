// SPDX-FileCopyrightText: 2005-2025 Quassel Project <devel@quassel-irc.org>
// SPDX-License-Identifier: GPL-2.0-or-later

#include "coreauthhandler.h"

#include <QSslSocket>
#include <QtEndian>

#include "core.h"

CoreAuthHandler::CoreAuthHandler(QSslSocket* socket, QObject* parent)
    : AuthHandler(parent)
    , _peer(nullptr)
    , _metricsServer(Core::instance()->metricsServer())
    , _proxyReceived(false)
    , _proxyLine({})
    , _useProxyLine(false)
    , _magicReceived(false)
    , _legacy(false)
    , _clientRegistered(false)
    , _connectionFeatures(0)
{
    setSocket(socket);
    connect(socket, &QIODevice::readyRead, this, &CoreAuthHandler::onReadyRead);

    // TODO: Timeout for the handshake phase
}

void CoreAuthHandler::onReadyRead()
{
    // once we have selected a peer, we certainly don't want to read more data!
    if (_peer)
        return;

    if (!_proxyReceived) {
        quint32 magic;
        socket()->peek((char*)&magic, 4);
        magic = qFromBigEndian<quint32>(magic);

        if (magic == QuasselProtocol::proxyMagic) {
            if (!socket()->canReadLine()) {
                return;
            }
            QByteArray line = socket()->readLine(108);
            _proxyLine = ProxyLine::parseProxyLine(line);
            if (_proxyLine.protocol != QAbstractSocket::UnknownNetworkLayerProtocol) {
                QList<QString> subnets = Quassel::optionValue("proxy-cidr").split(",");
                for (const QString& subnet : subnets) {
                    if (socket()->peerAddress().isInSubnet(QHostAddress::parseSubnet(subnet))) {
                        _useProxyLine = true;
                        break;
                    }
                }
            }
        }
        _proxyReceived = true;
    }

    if (socket()->bytesAvailable() < 4)
        return;

    if (!_magicReceived) {
        quint32 magic;
        socket()->peek((char*)&magic, 4);
        magic = qFromBigEndian<quint32>(magic);

        if ((magic & 0xffffff00) != QuasselProtocol::magic) {
            // no magic, assume legacy protocol
            qDebug() << "Legacy client detected, switching to compatibility mode";
            _legacy = true;
            RemotePeer* peer = PeerFactory::createPeer(PeerFactory::ProtoDescriptor(QuasselProtocol::LegacyProtocol, 0),
                                                       this,
                                                       socket(),
                                                       Compressor::NoCompression,
                                                       this);
            connect(peer, &RemotePeer::protocolVersionMismatch, this, &CoreAuthHandler::onProtocolVersionMismatch);
            setPeer(peer);
            return;
        }

        _magicReceived = true;
        quint8 features = magic & 0xff;
        // figure out which connection features we'll use based on the client's support
        if (Core::sslSupported() && (features & QuasselProtocol::Encryption))
            _connectionFeatures |= QuasselProtocol::Encryption;
        if (features & QuasselProtocol::Compression)
            _connectionFeatures |= QuasselProtocol::Compression;

        socket()->read((char*)&magic, 4);  // read the 4 bytes we've just peeked at
    }

    // read the list of protocols supported by the client
    while (socket()->bytesAvailable() >= 4 && _supportedProtos.size() < 16) {  // sanity check
        quint32 data;
        socket()->read((char*)&data, 4);
        data = qFromBigEndian<quint32>(data);

        auto type = static_cast<QuasselProtocol::Type>(data & 0xff);
        auto protoFeatures = static_cast<quint16>(data >> 8 & 0xffff);
        _supportedProtos.append(PeerFactory::ProtoDescriptor(type, protoFeatures));

        if (data >= 0x80000000) {  // last protocol
            Compressor::CompressionLevel level;
            if (_connectionFeatures & QuasselProtocol::Compression)
                level = Compressor::BestCompression;
            else
                level = Compressor::NoCompression;

            RemotePeer* peer = PeerFactory::createPeer(_supportedProtos, this, socket(), level, this);
            if (!peer) {
                qWarning() << "Received invalid handshake data from client" << hostAddress().toString();
                close();
                return;
            }

            if (peer->protocol() == QuasselProtocol::LegacyProtocol) {
                _legacy = true;
                connect(peer, &RemotePeer::protocolVersionMismatch, this, &CoreAuthHandler::onProtocolVersionMismatch);
            }
            setPeer(peer);

            // inform the client
            quint32 reply = peer->protocol() | peer->enabledFeatures() << 8 | _connectionFeatures << 24;
            reply = qToBigEndian<quint32>(reply);
            socket()->write((char*)&reply, 4);
            socket()->flush();

            if (!_legacy && (_connectionFeatures & QuasselProtocol::Encryption))
                startSsl();  // legacy peer enables it later
            return;
        }
    }
}

void CoreAuthHandler::setPeer(RemotePeer* peer)
{
    qDebug().nospace() << "Using " << qPrintable(peer->protocolName()) << "...";

    _peer = peer;
    if (_proxyLine.protocol != QAbstractSocket::UnknownNetworkLayerProtocol) {
        _peer->setProxyLine(_proxyLine);
    }
    disconnect(socket(), &QIODevice::readyRead, this, &CoreAuthHandler::onReadyRead);
}

// only in compat mode
void CoreAuthHandler::onProtocolVersionMismatch(int actual, int expected)
{
    qWarning() << qPrintable(tr("Client")) << _peer->description() << qPrintable(tr("too old, rejecting."));
    QString errorString = tr("<b>Your Quassel Client is too old!</b><br>"
                             "This core needs at least client/core protocol version %1 (got: %2).<br>"
                             "Please consider upgrading your client.")
                              .arg(expected, actual);
    _peer->dispatch(QuasselProtocol::ClientDenied(errorString));
    _peer->close();
}

bool CoreAuthHandler::checkClientRegistered()
{
    if (!_clientRegistered) {
        qWarning() << qPrintable(tr("Client")) << qPrintable(hostAddress().toString())
                   << qPrintable(tr("did not send a registration message before trying to login, rejecting."));
        _peer->dispatch(QuasselProtocol::ClientDenied(
            tr("<b>Client not initialized!</b><br>You need to send a registration message before trying to login.")));
        _peer->close();
        return false;
    }
    return true;
}

void CoreAuthHandler::handle(const QuasselProtocol::RegisterClient& msg)
{
    bool useSsl;
    if (_legacy)
        useSsl = Core::sslSupported() && msg.sslSupported;
    else
        useSsl = _connectionFeatures & QuasselProtocol::Encryption;

    if (Quassel::isOptionSet("require-ssl") && !useSsl && !_peer->isLocal()) {
        qInfo() << qPrintable(tr("SSL required but non-SSL connection attempt from %1").arg(hostAddress().toString()));
        _peer->dispatch(
            QuasselProtocol::ClientDenied(tr("<b>SSL is required!</b><br>You need to use SSL in order to connect to this core.")));
        _peer->close();
        return;
    }

    _peer->setFeatures(std::move(msg.features));
    _peer->setBuildDate(msg.buildDate);
    _peer->setClientVersion(msg.clientVersion);

    QVariantList backends;
    QVariantList authenticators;
    bool configured = Core::isConfigured();
    if (!configured) {
        backends = Core::backendInfo();
        if (_peer->hasFeature(Quassel::Feature::Authenticators)) {
            authenticators = Core::authenticatorInfo();
        }
    }

    _peer->dispatch(QuasselProtocol::ClientRegistered(Quassel::Features{}, configured, backends, authenticators, useSsl));

    // useSsl is only used for the legacy protocol
    if (_legacy && useSsl)
        startSsl();

    _clientRegistered = true;
}

void CoreAuthHandler::handle(const QuasselProtocol::SetupData& msg)
{
    if (!checkClientRegistered())
        return;

    // The default parameter to authenticator is Database.
    // Maybe this should be hardcoded elsewhere, i.e. as a define.
    QString authenticator = msg.authenticator;
    qInfo() << "[" << authenticator << "]";
    if (authenticator.trimmed().isEmpty()) {
        authenticator = QString("Database");
    }

    QString result = Core::setup(msg.adminUser, msg.adminPassword, msg.backend, msg.setupData, authenticator, msg.authSetupData);
    if (!result.isEmpty())
        _peer->dispatch(QuasselProtocol::SetupFailed(result));
    else
        _peer->dispatch(QuasselProtocol::SetupDone());
}

void CoreAuthHandler::handle(const QuasselProtocol::Login& msg)
{
    if (!checkClientRegistered())
        return;

    if (!Core::isConfigured()) {
        qWarning() << qPrintable(tr("Client")) << qPrintable(hostAddress().toString())
                   << qPrintable(tr("attempted to login before the core was configured, rejecting."));
        _peer->dispatch(QuasselProtocol::ClientDenied(
            tr("<b>Attempted to login before core was configured!</b><br>The core must be configured before attempting to login.")));
        return;
    }

    // First attempt local auth using the real username and password.
    // If that fails, move onto the auth provider.

    // Check to see if the user has the "Database" authenticator configured.
    UserId uid = 0;
    if (Core::getUserAuthenticator(msg.user) == "Database") {
        uid = Core::validateUser(msg.user, msg.password);
    }

    // If they did not, *or* if the database login fails, try to use a different authenticator.
    // TODO: this logic should likely be moved into Core::authenticateUser in the future.
    // Right now a core can only have one authenticator configured; this might be something
    // to change in the future.
    if (uid == 0) {
        uid = Core::authenticateUser(msg.user, msg.password);
    }

    if (uid == 0) {
        qInfo() << qPrintable(tr("Invalid login attempt from %1 as \"%2\"").arg(hostAddress().toString(), msg.user));
        _peer->dispatch(QuasselProtocol::LoginFailed(tr(
            "<b>Invalid username or password!</b><br>The username/password combination you supplied could not be found in the database.")));
        if (_metricsServer) {
            _metricsServer->addLoginAttempt(msg.user, false);
        }
        return;
    }
    _peer->dispatch(QuasselProtocol::LoginSuccess());
    if (_metricsServer) {
        _metricsServer->addLoginAttempt(uid, true);
    }

    qInfo() << qPrintable(tr("Client %1 initialized and authenticated successfully as \"%2\" (UserId: %3).")
                              .arg(_peer->address(), msg.user, QString::number(uid.toInt())));

    const auto& clientFeatures = _peer->features();
    auto unsupported = clientFeatures.toStringList(false);
    if (!unsupported.isEmpty()) {
        if (unsupported.contains("NoFeatures"))
            qInfo() << qPrintable(tr("Client does not support extended features."));
        else
            qInfo() << qPrintable(tr("Client does not support the following features: %1").arg(unsupported.join(", ")));
    }

    if (!clientFeatures.unknownFeatures().isEmpty()) {
        qInfo() << qPrintable(tr("Client supports unknown features: %1").arg(clientFeatures.unknownFeatures().join(", ")));
    }

    disconnect(socket(), nullptr, this, nullptr);
    disconnect(_peer, nullptr, this, nullptr);
    _peer->setParent(nullptr);  // Core needs to take care of this one now!

    socket()->flush();  // Make sure all data is sent before handing over the peer (and socket) to the session thread (bug 682)
    emit handshakeComplete(_peer, uid);
}

QHostAddress CoreAuthHandler::hostAddress() const
{
    if (_useProxyLine) {
        return _proxyLine.sourceHost;
    }
    else if (socket()) {
        return socket()->peerAddress();
    }

    return {};
}

bool CoreAuthHandler::isLocal() const
{
    return hostAddress() == QHostAddress::LocalHost || hostAddress() == QHostAddress::LocalHostIPv6;
}

/*** SSL Stuff ***/

void CoreAuthHandler::startSsl()
{
    qDebug() << qPrintable(tr("Starting encryption for Client:")) << _peer->description();
    connect(socket(), selectOverload<const QList<QSslError>&>(&QSslSocket::sslErrors), this, &CoreAuthHandler::onSslErrors);
    socket()->flush();  // ensure that the write cache is flushed before we switch to ssl (bug 682)
    socket()->startServerEncryption();
}

void CoreAuthHandler::onSslErrors()
{
    socket()->ignoreSslErrors();
}
