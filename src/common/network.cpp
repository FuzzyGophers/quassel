/***************************************************************************
 *   Copyright (C) 2005-2022 by the Quassel Project                        *
 *   devel@quassel-irc.org                                                 *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) version 3.                                           *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   You should have received a copy of the GNU General Public License     *
 *   along with this program; if not, write to the                         *
 *   Free Software Foundation, Inc.,                                       *
 *   51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.         *
 ***************************************************************************/

#include "network.h"

#include <algorithm>

#include <QDebug>
#include <QStringConverter>

#include "peer.h"

// Static default
const QStringConverter::Encoding Network::_defaultEncoding = QStringConverter::Utf8;

// ====================
//  Public:
// ====================

Network::Network(const NetworkId& networkid, QObject* parent)
    : SyncableObject(parent)
    , _proxy(nullptr)
    , _networkId(networkid)
    , _identity(0)
    , _myNick(QString())
    , _latency(0)
    , _networkName(QString("<not initialized>"))
    , _currentServer(QString())
    , _connected(false)
    , _connectionState(Disconnected)
    , _prefixes(QString())
    , _prefixModes(QString())
    , _useRandomServer(false)
    , _useAutoIdentify(false)
    , _useSasl(false)
    , _useAutoReconnect(false)
    , _autoReconnectInterval(60)
    , _autoReconnectRetries(10)
    , _unlimitedReconnectRetries(false)
    , _useCustomMessageRate(false)
    , _messageRateBurstSize(5)
    , _messageRateDelay(2200)
    , _unlimitedMessageRate(false)
    , _serverEncoder(_defaultEncoding)
    , _serverDecoder(_defaultEncoding)
    , _encoder(_defaultEncoding)
    , _decoder(_defaultEncoding)
    , _autoAwayActive(false)
{
    setObjectName(QString::number(networkid.toInt()));
}

Network::~Network()
{
    emit aboutToBeDestroyed();
}

bool Network::isChannelName(const QString& channelname) const
{
    if (channelname.isEmpty())
        return false;

    if (supports("CHANTYPES"))
        return support("CHANTYPES").contains(channelname[0]);
    else
        return QString("#&!+").contains(channelname[0]);
}

bool Network::isStatusMsg(const QString& target) const
{
    if (target.isEmpty())
        return false;

    if (supports("STATUSMSG"))
        return support("STATUSMSG").contains(target[0]);
    else
        return QString("@+").contains(target[0]);
}

NetworkInfo Network::networkInfo() const
{
    NetworkInfo info;
    info.networkName = networkName();
    info.networkId = networkId();
    info.identity = identity();
    info.codecForServer = codecForServer();
    info.codecForEncoding = codecForEncoding();
    info.codecForDecoding = codecForDecoding();
    info.serverList = serverList();
    info.useRandomServer = useRandomServer();
    info.perform = perform();
    info.skipCaps = skipCaps();
    info.useAutoIdentify = useAutoIdentify();
    info.autoIdentifyService = autoIdentifyService();
    info.autoIdentifyPassword = autoIdentifyPassword();
    info.useSasl = useSasl();
    info.saslAccount = saslAccount();
    info.saslPassword = saslPassword();
    info.useAutoReconnect = useAutoReconnect();
    info.autoReconnectInterval = autoReconnectInterval();
    info.autoReconnectRetries = autoReconnectRetries();
    info.unlimitedReconnectRetries = unlimitedReconnectRetries();
    info.rejoinChannels = rejoinChannels();
    info.useCustomMessageRate = useCustomMessageRate();
    info.messageRateBurstSize = messageRateBurstSize();
    info.messageRateDelay = messageRateDelay();
    info.unlimitedMessageRate = unlimitedMessageRate();
    return info;
}

void Network::setNetworkInfo(const NetworkInfo& info)
{
    if (!info.networkName.isEmpty() && info.networkName != networkName())
        setNetworkName(info.networkName);
    if (info.identity > 0 && info.identity != identity())
        setIdentity(info.identity);
    if (info.codecForServer != codecForServer())
        setCodecForServer(info.codecForServer);
    if (info.codecForEncoding != codecForEncoding())
        setCodecForEncoding(info.codecForEncoding);
    if (info.codecForDecoding != codecForDecoding())
        setCodecForDecoding(info.codecForDecoding);
    if (info.serverList.count())
        setServerList(toVariantList(info.serverList));
    if (info.useRandomServer != useRandomServer())
        setUseRandomServer(info.useRandomServer);
    if (info.perform != perform())
        setPerform(info.perform);
    if (info.skipCaps != skipCaps())
        setSkipCaps(info.skipCaps);
    if (info.useAutoIdentify != useAutoIdentify())
        setUseAutoIdentify(info.useAutoIdentify);
    if (info.autoIdentifyService != autoIdentifyService())
        setAutoIdentifyService(info.autoIdentifyService);
    if (info.autoIdentifyPassword != autoIdentifyPassword())
        setAutoIdentifyPassword(info.autoIdentifyPassword);
    if (info.useSasl != useSasl())
        setUseSasl(info.useSasl);
    if (info.saslAccount != saslAccount())
        setSaslAccount(info.saslAccount);
    if (info.saslPassword != saslPassword())
        setSaslPassword(info.saslPassword);
    if (info.useAutoReconnect != useAutoReconnect())
        setUseAutoReconnect(info.useAutoReconnect);
    if (info.autoReconnectInterval != autoReconnectInterval())
        setAutoReconnectInterval(info.autoReconnectInterval);
    if (info.autoReconnectRetries != autoReconnectRetries())
        setAutoReconnectRetries(info.autoReconnectRetries);
    if (info.unlimitedReconnectRetries != unlimitedReconnectRetries())
        setUnlimitedReconnectRetries(info.unlimitedReconnectRetries);
    if (info.rejoinChannels != rejoinChannels())
        setRejoinChannels(info.rejoinChannels);
    if (info.useCustomMessageRate != useCustomMessageRate())
        setUseCustomMessageRate(info.useCustomMessageRate);
    if (info.messageRateBurstSize != messageRateBurstSize())
        setMessageRateBurstSize(info.messageRateBurstSize);
    if (info.messageRateDelay != messageRateDelay())
        setMessageRateDelay(info.messageRateDelay);
    if (info.unlimitedMessageRate != unlimitedMessageRate())
        setUnlimitedMessageRate(info.unlimitedMessageRate);
}

QString Network::prefixToMode(const QString& prefix) const
{
    if (prefixes().contains(prefix))
        return QString(prefixModes()[prefixes().indexOf(prefix)]);
    else
        return QString();
}

QString Network::modeToPrefix(const QString& mode) const
{
    if (prefixModes().contains(mode))
        return QString(prefixes()[prefixModes().indexOf(mode)]);
    else
        return QString();
}

QString Network::sortPrefixModes(const QString& modes) const
{
    if (modes.isEmpty() || prefixModes().isEmpty()) {
        return modes;
    }

    QString sortedModes = QString(modes);
    std::sort(sortedModes.begin(), sortedModes.end(), [&](const QChar& lmode, const QChar& rmode) {
        if (!prefixModes().contains(lmode)) {
            return false;
        }
        else if (!prefixModes().contains(rmode)) {
            return true;
        }
        else {
            return (prefixModes().indexOf(lmode) < prefixModes().indexOf(rmode));
        }
    });

    return sortedModes;
}

QStringList Network::nicks() const
{
    QStringList nicks;
    foreach (IrcUser* ircuser, _ircUsers.values()) {
        nicks << ircuser->nick();
    }
    return nicks;
}

QString Network::prefixes() const
{
    if (_prefixes.isNull())
        determinePrefixes();

    return _prefixes;
}

QString Network::prefixModes() const
{
    if (_prefixModes.isNull())
        determinePrefixes();

    return _prefixModes;
}

Network::ChannelModeType Network::channelModeType(const QString& mode)
{
    if (mode.isEmpty())
        return NOT_A_CHANMODE;

    QString chanmodes = support("CHANMODES");
    if (chanmodes.isEmpty())
        return NOT_A_CHANMODE;

    ChannelModeType modeType = A_CHANMODE;
    for (int i = 0; i < chanmodes.count(); i++) {
        if (chanmodes[i] == mode[0])
            break;
        else if (chanmodes[i] == ',')
            modeType = (ChannelModeType)(modeType << 1);
    }
    if (modeType > D_CHANMODE) {
        qWarning() << "Network" << networkId() << "supplied invalid CHANMODES:" << chanmodes;
        modeType = NOT_A_CHANMODE;
    }
    return modeType;
}

QString Network::support(const QString& param) const
{
    QString support_ = param.toUpper();
    if (_supports.contains(support_))
        return _supports[support_];
    else
        return QString();
}

bool Network::saslMaybeSupports(const QString& saslMechanism) const
{
    if (!capAvailable(IrcCap::SASL)) {
        return false;
    }

    QString saslCapValue = capValue(IrcCap::SASL);
    return (saslCapValue.length() == 0) || (saslCapValue.contains(saslMechanism, Qt::CaseInsensitive));
}

IrcUser* Network::newIrcUser(const QString& hostmask, const QVariantMap& initData)
{
    QString nick(nickFromMask(hostmask).toLower());
    if (!_ircUsers.contains(nick)) {
        IrcUser* ircuser = ircUserFactory(hostmask);
        if (!initData.isEmpty()) {
            ircuser->fromVariantMap(initData);
            ircuser->setInitialized();
        }

        if (proxy())
            proxy()->synchronize(ircuser);
        else
            qWarning() << "unable to synchronize new IrcUser" << hostmask << "forgot to call Network::setProxy(SignalProxy *)?";

        connect(ircuser, &IrcUser::nickSet, this, &Network::ircUserNickChanged);

        _ircUsers[nick] = ircuser;

        QString mask = ircuser->hostmask();
        SYNC_OTHER(addIrcUser, ARG(mask));
        emit ircUserAdded(ircuser);
    }

    return _ircUsers[nick];
}

IrcUser* Network::ircUser(QString nickname) const
{
    nickname = nickname.toLower();
    if (_ircUsers.contains(nickname))
        return _ircUsers[nickname];
    else
        return nullptr;
}

void Network::removeIrcUser(IrcUser* ircuser)
{
    QString nick = _ircUsers.key(ircuser);
    if (nick.isNull())
        return;

    _ircUsers.remove(nick);
    disconnect(ircuser, nullptr, this, nullptr);
    ircuser->deleteLater();
}

void Network::removeIrcChannel(IrcChannel* channel)
{
    QString chanName = _ircChannels.key(channel);
    if (chanName.isNull())
        return;

    _ircChannels.remove(chanName);
    disconnect(channel, nullptr, this, nullptr);
    channel->deleteLater();
}

void Network::removeChansAndUsers()
{
    QList<IrcUser*> users = ircUsers();
    _ircUsers.clear();
    QList<IrcChannel*> channels = ircChannels();
    _ircChannels.clear();

    qDeleteAll(users);
    qDeleteAll(channels);
}

IrcChannel* Network::newIrcChannel(const QString& channelname, const QVariantMap& initData)
{
    if (!_ircChannels.contains(channelname.toLower())) {
        IrcChannel* channel = ircChannelFactory(channelname);
        if (!initData.isEmpty()) {
            channel->fromVariantMap(initData);
            channel->setInitialized();
        }

        if (proxy())
            proxy()->synchronize(channel);
        else
            qWarning() << "unable to synchronize new IrcChannel" << channelname << "forgot to call Network::setProxy(SignalProxy *)?";

        _ircChannels[channelname.toLower()] = channel;

        SYNC_OTHER(addIrcChannel, ARG(channelname))
        emit ircChannelAdded(channel);
    }
    return _ircChannels[channelname.toLower()];
}

IrcChannel* Network::ircChannel(QString channelname) const
{
    channelname = channelname.toLower();
    if (_ircChannels.contains(channelname))
        return _ircChannels[channelname];
    else
        return nullptr;
}

QString Network::defaultCodecForServer()
{
    return QStringConverter::nameForEncoding(_defaultEncoding);
}

void Network::setDefaultCodecForServer(const QString& name)
{
    QStringConverter::Encoding encoding = QStringConverter::encodingForName(name.toUtf8().constData()).value_or(_defaultEncoding);
    // No need to store, as _defaultEncoding is static and immutable
}

QString Network::defaultCodecForEncoding()
{
    return QStringConverter::nameForEncoding(_defaultEncoding);
}

void Network::setDefaultCodecForEncoding(const QString& name)
{
    // No need to store, as _defaultEncoding is static and immutable
}

QString Network::defaultCodecForDecoding()
{
    return QStringConverter::nameForEncoding(_defaultEncoding);
}

void Network::setDefaultCodecForDecoding(const QString& name)
{
    // No need to store, as _defaultEncoding is static and immutable
}

QString Network::codecForServer() const
{
    return QStringConverter::nameForEncoding(_serverEncoder.encoding());
}

void Network::setCodecForServer(const QString& name)
{
    QStringConverter::Encoding encoding = QStringConverter::encodingForName(name.toUtf8().constData()).value_or(_defaultEncoding);
    setCodecForServer(encoding);
}

void Network::setCodecForServer(QStringConverter::Encoding encoding)
{
    _serverEncoder = QStringEncoder(encoding);
    _serverDecoder = QStringDecoder(encoding);
    if (!_serverEncoder.isValid() || !_serverDecoder.isValid()) {
        qWarning() << "Invalid server encoding/decoding for" << QStringConverter::nameForEncoding(encoding) << ", falling back to default";
        _serverEncoder = QStringEncoder(_defaultEncoding);
        _serverDecoder = QStringDecoder(_defaultEncoding);
    }
    QString codecName = codecForServer();
    SYNC_OTHER(setCodecForServer, ARG(codecName))
    emit configChanged();
}

QString Network::codecForEncoding() const
{
    return QStringConverter::nameForEncoding(_encoder.encoding());
}

void Network::setCodecForEncoding(const QString& name)
{
    QStringConverter::Encoding encoding = QStringConverter::encodingForName(name.toUtf8().constData()).value_or(_defaultEncoding);
    setCodecForEncoding(encoding);
}

void Network::setCodecForEncoding(QStringConverter::Encoding encoding)
{
    _encoder = QStringEncoder(encoding);
    if (!_encoder.isValid()) {
        qWarning() << "Invalid encoding for" << QStringConverter::nameForEncoding(encoding) << ", falling back to default";
        _encoder = QStringEncoder(_defaultEncoding);
    }
    QString codecName = codecForEncoding();
    SYNC_OTHER(setCodecForEncoding, ARG(codecName))
    emit configChanged();
}

QString Network::codecForDecoding() const
{
    return QStringConverter::nameForEncoding(_decoder.encoding());
}

void Network::setCodecForDecoding(const QString& name)
{
    QStringConverter::Encoding encoding = QStringConverter::encodingForName(name.toUtf8().constData()).value_or(_defaultEncoding);
    setCodecForDecoding(encoding);
}

void Network::setCodecForDecoding(QStringConverter::Encoding encoding)
{
    _decoder = QStringDecoder(encoding);
    if (!_decoder.isValid()) {
        qWarning() << "Invalid decoding for" << QStringConverter::nameForEncoding(encoding) << ", falling back to default";
        _decoder = QStringDecoder(_defaultEncoding);
    }
    QString codecName = codecForDecoding();
    SYNC_OTHER(setCodecForDecoding, ARG(codecName))
    emit configChanged();
}

// Assuming ::decodeString from prior migration
static QString decodeString(const QByteArray& input, std::optional<QStringDecoder> decoder = std::nullopt)
{
    static const QSet<QStringConverter::Encoding> utf8DetectionBlacklist = {QStringConverter::Latin1};
    if (decoder && utf8DetectionBlacklist.contains(decoder->encoding())) {
        QString result = decoder->operator()(input);
        if (decoder->hasError()) {
            qWarning() << "Decoding error with provided decoder for input:" << input;
        }
        return result;
    }

    bool isUtf8 = true;
    int cnt = 0;
    for (uchar c : input) {
        if (cnt) {
            if ((c & 0xc0) != 0x80) {
                isUtf8 = false;
                break;
            }
            cnt--;
            continue;
        }
        if ((c & 0x80) == 0x00)
            continue;
        if ((c & 0xf8) == 0xf0) {
            cnt = 3;
            continue;
        }
        if ((c & 0xf0) == 0xe0) {
            cnt = 2;
            continue;
        }
        if ((c & 0xe0) == 0xc0) {
            cnt = 1;
            continue;
        }
        isUtf8 = false;
        break;
    }

    if (isUtf8 && cnt == 0) {
        QString s = QString::fromUtf8(input);
        return s;
    }

    QStringDecoder defaultDecoder = decoder.value_or(QStringDecoder(QStringConverter::Latin1));
    QString result = defaultDecoder(input);
    if (defaultDecoder.hasError()) {
        qWarning() << "Decoding error with" << (decoder ? "provided decoder" : "Latin1") << "for input:" << input;
    }
    return result;
}

QString Network::decodeString(const QByteArray& text) const
{
    if (_decoder.isValid()) {
        return ::decodeString(text, _decoder);
    }
    return ::decodeString(text, std::nullopt); // Uses default (Latin1)
}

QByteArray Network::encodeString(const QString& string) const
{
    if (_encoder.isValid()) {
        return _encoder(string);
    }
    return QStringEncoder(_defaultEncoding)(string);
}

QString Network::decodeServerString(const QByteArray& text) const
{
    if (_serverDecoder.isValid()) {
        return ::decodeString(text, _serverDecoder);
    }
    return ::decodeString(text, std::nullopt); // Uses default (Latin1)
}

QByteArray Network::encodeServerString(const QString& string) const
{
    if (_serverEncoder.isValid()) {
        return _serverEncoder(string);
    }
    return QStringEncoder(_defaultEncoding)(string);
}

// ====================
//  Public Slots:
// ====================
void Network::setNetworkName(const QString& networkName)
{
    _networkName = networkName;
    SYNC(ARG(networkName))
    emit networkNameSet(networkName);
    emit configChanged();
}

void Network::setCurrentServer(const QString& currentServer)
{
    _currentServer = currentServer;
    SYNC(ARG(currentServer))
    emit currentServerSet(currentServer);
}

void Network::setConnected(bool connected)
{
    if (_connected == connected)
        return;

    _connected = connected;
    if (!connected) {
        setMyNick(QString());
        setCurrentServer(QString());
        removeChansAndUsers();
    }
    SYNC(ARG(connected))
    emit connectedSet(connected);
}

void Network::setConnectionState(int state)
{
    _connectionState = (ConnectionState)state;
    SYNC(ARG(state))
    emit connectionStateSet(_connectionState);
}

void Network::setMyNick(const QString& nickname)
{
    _myNick = nickname;
    if (!_myNick.isEmpty() && !ircUser(myNick())) {
        newIrcUser(myNick());
    }
    SYNC(ARG(nickname))
    emit myNickSet(nickname);
}

void Network::setLatency(int latency)
{
    if (_latency == latency)
        return;
    _latency = latency;
    SYNC(ARG(latency))
}

void Network::setIdentity(IdentityId id)
{
    _identity = id;
    SYNC(ARG(id))
    emit identitySet(id);
    emit configChanged();
}

void Network::setServerList(const QVariantList& serverList)
{
    _serverList = fromVariantList<Server>(serverList);
    SYNC(ARG(serverList))
    emit configChanged();
}

void Network::setUseRandomServer(bool use)
{
    _useRandomServer = use;
    SYNC(ARG(use))
    emit configChanged();
}

void Network::setPerform(const QStringList& perform)
{
    _perform = perform;
    SYNC(ARG(perform))
    emit configChanged();
}

void Network::setSkipCaps(const QStringList& skipCaps)
{
    _skipCaps = skipCaps;
    _skipCaps.sort();
    SYNC(ARG(skipCaps))
    emit configChanged();
}

void Network::setUseAutoIdentify(bool use)
{
    _useAutoIdentify = use;
    SYNC(ARG(use))
    emit configChanged();
}

void Network::setAutoIdentifyService(const QString& service)
{
    _autoIdentifyService = service;
    SYNC(ARG(service))
    emit configChanged();
}

void Network::setAutoIdentifyPassword(const QString& password)
{
    _autoIdentifyPassword = password;
    SYNC(ARG(password))
    emit configChanged();
}

void Network::setUseSasl(bool use)
{
    _useSasl = use;
    SYNC(ARG(use))
    emit configChanged();
}

void Network::setSaslAccount(const QString& account)
{
    _saslAccount = account;
    SYNC(ARG(account))
    emit configChanged();
}

void Network::setSaslPassword(const QString& password)
{
    _saslPassword = password;
    SYNC(ARG(password))
    emit configChanged();
}

void Network::setUseAutoReconnect(bool use)
{
    _useAutoReconnect = use;
    SYNC(ARG(use))
    emit configChanged();
}

void Network::setAutoReconnectInterval(quint32 interval)
{
    _autoReconnectInterval = interval;
    SYNC(ARG(interval))
    emit configChanged();
}

void Network::setAutoReconnectRetries(quint16 retries)
{
    _autoReconnectRetries = retries;
    SYNC(ARG(retries))
    emit configChanged();
}

void Network::setUnlimitedReconnectRetries(bool unlimited)
{
    _unlimitedReconnectRetries = unlimited;
    SYNC(ARG(unlimited))
    emit configChanged();
}

void Network::setRejoinChannels(bool rejoin)
{
    _rejoinChannels = rejoin;
    SYNC(ARG(rejoin))
    emit configChanged();
}

void Network::setUseCustomMessageRate(bool useCustomRate)
{
    if (_useCustomMessageRate != useCustomRate) {
        _useCustomMessageRate = useCustomRate;
        SYNC(ARG(useCustomRate))
        emit configChanged();
        emit useCustomMessageRateSet(_useCustomMessageRate);
    }
}

void Network::setMessageRateBurstSize(quint32 burstSize)
{
    if (burstSize < 1) {
        qDebug() << "Received invalid setMessageRateBurstSize data - message burst size must be "
                    "non-zero positive, given"
                 << burstSize;
        return;
    }
    if (_messageRateBurstSize != burstSize) {
        _messageRateBurstSize = burstSize;
        SYNC(ARG(burstSize))
        emit configChanged();
        emit messageRateBurstSizeSet(_messageRateBurstSize);
    }
}

void Network::setMessageRateDelay(quint32 messageDelay)
{
    if (messageDelay == 0) {
        qDebug() << "Received invalid setMessageRateDelay data - message delay must be non-zero "
                    "positive, given"
                 << messageDelay;
        return;
    }
    if (_messageRateDelay != messageDelay) {
        _messageRateDelay = messageDelay;
        SYNC(ARG(messageDelay))
        emit configChanged();
        emit messageRateDelaySet(_messageRateDelay);
    }
}

void Network::setUnlimitedMessageRate(bool unlimitedRate)
{
    if (_unlimitedMessageRate != unlimitedRate) {
        _unlimitedMessageRate = unlimitedRate;
        SYNC(ARG(unlimitedRate))
        emit configChanged();
        emit unlimitedMessageRateSet(_unlimitedMessageRate);
    }
}

void Network::addSupport(const QString& param, const QString& value)
{
    if (!_supports.contains(param)) {
        _supports[param] = value;
        SYNC(ARG(param), ARG(value))
    }
}

void Network::removeSupport(const QString& param)
{
    if (_supports.contains(param)) {
        _supports.remove(param);
        SYNC(ARG(param))
    }
}

QVariantMap Network::initSupports() const
{
    QVariantMap supports;
    QHashIterator<QString, QString> iter(_supports);
    while (iter.hasNext()) {
        iter.next();
        supports[iter.key()] = iter.value();
    }
    return supports;
}

void Network::addCap(const QString& capability, const QString& value)
{
    QString _capLowercase = capability.toLower();
    if (!_caps.contains(_capLowercase)) {
        _caps[_capLowercase] = value;
        SYNC(ARG(capability), ARG(value))
        emit capAdded(_capLowercase);
    }
}

void Network::acknowledgeCap(const QString& capability)
{
    QString _capLowercase = capability.toLower();
    if (!_capsEnabled.contains(_capLowercase)) {
        _capsEnabled.append(_capLowercase);
        SYNC(ARG(capability))
        emit capAcknowledged(_capLowercase);
    }
}

void Network::removeCap(const QString& capability)
{
    QString _capLowercase = capability.toLower();
    if (_caps.contains(_capLowercase)) {
        _caps.remove(_capLowercase);
        _capsEnabled.removeOne(_capLowercase);
        SYNC(ARG(capability))
        emit capRemoved(_capLowercase);
    }
}

void Network::clearCaps()
{
    if (_caps.empty() && _capsEnabled.empty()) {
        return;
    }
    QString _capLowercase;
    foreach (const QString& capability, _caps) {
        _capLowercase = capability.toLower();
        emit capRemoved(_capLowercase);
    }
    _caps.clear();
    _capsEnabled.clear();

    SYNC(NO_ARG)
}

QVariantMap Network::initCaps() const
{
    QVariantMap caps;
    QHashIterator<QString, QString> iter(_caps);
    while (iter.hasNext()) {
        iter.next();
        caps[iter.key()] = iter.value();
    }
    return caps;
}

QVariantMap Network::initIrcUsersAndChannels() const
{
    Q_ASSERT(proxy());
    Q_ASSERT(proxy()->targetPeer());
    QVariantMap usersAndChannels;

    if (_ircUsers.count()) {
        QHash<QString, QVariantList> users;
        QHash<QString, IrcUser*>::const_iterator it = _ircUsers.begin();
        QHash<QString, IrcUser*>::const_iterator end = _ircUsers.end();
        while (it != end) {
            QVariantMap map = it.value()->toVariantMap();
            if (!proxy()->targetPeer()->hasFeature(Quassel::Feature::LongTime)) {
#if QT_VERSION >= 0x050800
                int lastAwayMessage = it.value()->lastAwayMessageTime().toSecsSinceEpoch();
#else
                int lastAwayMessage = it.value()->lastAwayMessageTime().toMSecsSinceEpoch() / 1000;
#endif
                map.remove("lastAwayMessageTime");
                map["lastAwayMessage"] = lastAwayMessage;
            }

            QVariantMap::const_iterator mapiter = map.begin();
            while (mapiter != map.end()) {
                users[mapiter.key()] << mapiter.value();
                ++mapiter;
            }
            ++it;
        }
        QVariantMap userMap;
        foreach (const QString& key, users.keys())
            userMap[key] = users[key];
        usersAndChannels["Users"] = userMap;
    }

    if (_ircChannels.count()) {
        QHash<QString, QVariantList> channels;
        QHash<QString, IrcChannel*>::const_iterator it = _ircChannels.begin();
        QHash<QString, IrcChannel*>::const_iterator end = _ircChannels.end();
        while (it != end) {
            const QVariantMap& map = it.value()->toVariantMap();
            QVariantMap::const_iterator mapiter = map.begin();
            while (mapiter != map.end()) {
                channels[mapiter.key()] << mapiter.value();
                ++mapiter;
            }
            ++it;
        }
        QVariantMap channelMap;
        foreach (const QString& key, channels.keys())
            channelMap[key] = channels[key];
        usersAndChannels["Channels"] = channelMap;
    }

    return usersAndChannels;
}

void Network::initSetIrcUsersAndChannels(const QVariantMap& usersAndChannels)
{
    Q_ASSERT(proxy());
    Q_ASSERT(proxy()->sourcePeer());
    if (isInitialized()) {
        qWarning() << "Network" << networkId()
                   << "received init data for users and channels although there already are known users or channels!";
        return;
    }

    const QVariantMap& users = usersAndChannels["Users"].toMap();

    int count = users["nick"].toList().count();
    foreach (const QString& key, users.keys()) {
        if (users[key].toList().count() != count) {
            qWarning() << "Received invalid usersAndChannels init data, sizes of attribute lists don't match!";
            return;
        }
    }

    for (int i = 0; i < count; i++) {
        QVariantMap map;
        foreach (const QString& key, users.keys())
            map[key] = users[key].toList().at(i);

        if (!proxy()->sourcePeer()->hasFeature(Quassel::Feature::LongTime)) {
            QDateTime lastAwayMessageTime = QDateTime();
            lastAwayMessageTime.setTimeSpec(Qt::UTC);
#if QT_VERSION >= 0x050800
            lastAwayMessageTime.fromSecsSinceEpoch(map.take("lastAwayMessage").toInt());
#else
            lastAwayMessageTime.fromMSecsSinceEpoch(map.take("lastAwayMessage").toInt() * 1000);
#endif
            map["lastAwayMessageTime"] = lastAwayMessageTime;
        }

        newIrcUser(map["nick"].toString(), map);
    }

    const QVariantMap& channels = usersAndChannels["Channels"].toMap();

    count = channels["name"].toList().count();
    foreach (const QString& key, channels.keys()) {
        if (channels[key].toList().count() != count) {
            qWarning() << "Received invalid usersAndChannels init data, sizes of attribute lists don't match!";
            return;
        }
    }
    for (int i = 0; i < count; i++) {
        QVariantMap map;
        foreach (const QString& key, channels.keys())
            map[key] = channels[key].toList().at(i);
        newIrcChannel(map["name"].toString(), map);
    }
}

void Network::initSetSupports(const QVariantMap& supports)
{
    QMapIterator<QString, QVariant> iter(supports);
    while (iter.hasNext()) {
        iter.next();
        addSupport(iter.key(), iter.value().toString());
    }
}

void Network::initSetCaps(const QVariantMap& caps)
{
    QMapIterator<QString, QVariant> iter(caps);
    while (iter.hasNext()) {
        iter.next();
        addCap(iter.key(), iter.value().toString());
    }
}

IrcUser* Network::updateNickFromMask(const QString& mask)
{
    QString nick(nickFromMask(mask).toLower());
    IrcUser* ircuser;

    if (_ircUsers.contains(nick)) {
        ircuser = _ircUsers[nick];
        ircuser->updateHostmask(mask);
    }
    else {
        ircuser = newIrcUser(mask);
    }
    return ircuser;
}

void Network::ircUserNickChanged(QString newnick)
{
    QString oldnick = _ircUsers.key(qobject_cast<IrcUser*>(sender()));

    if (oldnick.isNull())
        return;

    if (newnick.toLower() != oldnick)
        _ircUsers[newnick.toLower()] = _ircUsers.take(oldnick);

    if (myNick().toLower() == oldnick)
        setMyNick(newnick);
}

void Network::emitConnectionError(const QString& errorMsg)
{
    emit connectionError(errorMsg);
}

// ====================
//  Private:
// ====================
void Network::determinePrefixes() const
{
    QString prefix = support("PREFIX");

    if (prefix.startsWith("(") && prefix.contains(")")) {
        _prefixes = prefix.section(")", 1);
        _prefixModes = prefix.mid(1).section(")", 0, 0);
    }
    else {
        QString defaultPrefixes("~&@%+");
        QString defaultPrefixModes("qaohv");

        if (prefix.isEmpty()) {
            _prefixes = defaultPrefixes;
            _prefixModes = defaultPrefixModes;
            return;
        }
        _prefixes = QString();
        _prefixModes = QString();

        for (int i = 0; i < defaultPrefixes.size(); i++) {
            if (prefix.contains(defaultPrefixes[i])) {
                _prefixes += defaultPrefixes[i];
                _prefixModes += defaultPrefixModes[i];
            }
        }
        if (!_prefixes.isNull())
            return;

        for (int i = 0; i < defaultPrefixes.size(); i++) {
            if (prefix.contains(defaultPrefixModes[i])) {
                _prefixes += defaultPrefixes[i];
                _prefixModes += defaultPrefixModes[i];
            }
        }
    }
}

/************************************************************************
 * NetworkInfo
 ************************************************************************/

QString NetworkInfo::skipCapsToString() const
{
    auto sortedSkipCaps = skipCaps;
    sortedSkipCaps.sort();
    return sortedSkipCaps.join(" ");
}

void NetworkInfo::skipCapsFromString(const QString& flattenedSkipCaps)
{
    skipCaps = flattenedSkipCaps.toLower().split(" ", QString::SplitBehavior::SkipEmptyParts);
}

bool NetworkInfo::operator==(const NetworkInfo& other) const
{
    return networkName == other.networkName
           && serverList == other.serverList
           && perform == other.perform
           && skipCaps == other.skipCaps
           && autoIdentifyService == other.autoIdentifyService
           && autoIdentifyPassword == other.autoIdentifyPassword
           && saslAccount == other.saslAccount
           && saslPassword == other.saslPassword
           && codecForServer == other.codecForServer
           && codecForEncoding == other.codecForEncoding
           && codecForDecoding == other.codecForDecoding
           && networkId == other.networkId
           && identity == other.identity
           && messageRateBurstSize == other.messageRateBurstSize
           && messageRateDelay == other.messageRateDelay
           && autoReconnectInterval == other.autoReconnectInterval
           && autoReconnectRetries == other.autoReconnectRetries
           && rejoinChannels == other.rejoinChannels
           && useRandomServer == other.useRandomServer
           && useAutoIdentify == other.useAutoIdentify
           && useSasl == other.useSasl
           && useAutoReconnect == other.useAutoReconnect
           && unlimitedReconnectRetries == other.unlimitedReconnectRetries
           && useCustomMessageRate == other.useCustomMessageRate
           && unlimitedMessageRate == other.unlimitedMessageRate;
}

bool NetworkInfo::operator!=(const NetworkInfo& other) const
{
    return !(*this == other);
}

QDataStream& operator<<(QDataStream& out, const NetworkInfo& info)
{
    QVariantMap i;
    i["NetworkName"] = info.networkName;
    i["ServerList"] = toVariantList(info.serverList);
    i["Perform"] = info.perform;
    i["SkipCaps"] = info.skipCaps;
    i["AutoIdentifyService"] = info.autoIdentifyService;
    i["AutoIdentifyPassword"] = info.autoIdentifyPassword;
    i["SaslAccount"] = info.saslAccount;
    i["SaslPassword"] = info.saslPassword;
    i["CodecForServer"] = info.codecForServer;
    i["CodecForEncoding"] = info.codecForEncoding;
    i["CodecForDecoding"] = info.codecForDecoding;
    i["NetworkId"] = QVariant::fromValue(info.networkId);
    i["Identity"] = QVariant::fromValue(info.identity);
    i["MessageRateBurstSize"] = info.messageRateBurstSize;
    i["MessageRateDelay"] = info.messageRateDelay;
    i["AutoReconnectInterval"] = info.autoReconnectInterval;
    i["AutoReconnectRetries"] = info.autoReconnectRetries;
    i["RejoinChannels"] = info.rejoinChannels;
    i["UseRandomServer"] = info.useRandomServer;
    i["UseAutoIdentify"] = info.useAutoIdentify;
    i["UseSasl"] = info.useSasl;
    i["UseAutoReconnect"] = info.useAutoReconnect;
    i["UnlimitedReconnectRetries"] = info.unlimitedReconnectRetries;
    i["UseCustomMessageRate"] = info.useCustomMessageRate;
    i["UnlimitedMessageRate"] = info.unlimitedMessageRate;
    out << i;
    return out;
}

QDataStream& operator>>(QDataStream& in, NetworkInfo& info)
{
    QVariantMap i;
    in >> i;
    info.networkName = i["NetworkName"].toString();
    info.serverList = fromVariantList<Network::Server>(i["ServerList"].toList());
    info.perform = i["Perform"].toStringList();
    info.skipCaps = i["SkipCaps"].toStringList();
    info.autoIdentifyService = i["AutoIdentifyService"].toString();
    info.autoIdentifyPassword = i["AutoIdentifyPassword"].toString();
    info.saslAccount = i["SaslAccount"].toString();
    info.saslPassword = i["SaslPassword"].toString();
    info.codecForServer = i["CodecForServer"].toString();
    info.codecForEncoding = i["CodecForEncoding"].toString();
    info.codecForDecoding = i["CodecForDecoding"].toString();
    info.networkId = i["NetworkId"].value<NetworkId>();
    info.identity = i["Identity"].value<IdentityId>();
    info.messageRateBurstSize = i["MessageRateBurstSize"].toUInt();
    info.messageRateDelay = i["MessageRateDelay"].toUInt();
    info.autoReconnectInterval = i["AutoReconnectInterval"].toUInt();
    info.autoReconnectRetries = i["AutoReconnectRetries"].toInt();
    info.rejoinChannels = i["RejoinChannels"].toBool();
    info.useRandomServer = i["UseRandomServer"].toBool();
    info.useAutoIdentify = i["UseAutoIdentify"].toBool();
    info.useSasl = i["UseSasl"].toBool();
    info.useAutoReconnect = i["UseAutoReconnect"].toBool();
    info.unlimitedReconnectRetries = i["UnlimitedReconnectRetries"].toBool();
    info.useCustomMessageRate = i["UseCustomMessageRate"].toBool();
    info.unlimitedMessageRate = i["UnlimitedMessageRate"].toBool();
    return in;
}

QDebug operator<<(QDebug dbg, const NetworkInfo& i)
{
    dbg.nospace() << "(id = " << i.networkId << " name = " << i.networkName << " identity = " << i.identity
                  << " codecForServer = " << i.codecForServer << " codecForEncoding = " << i.codecForEncoding
                  << " codecForDecoding = " << i.codecForDecoding << " serverList = " << i.serverList
                  << " useRandomServer = " << i.useRandomServer << " perform = " << i.perform
                  << " skipCaps = " << i.skipCaps << " useAutoIdentify = " << i.useAutoIdentify
                  << " autoIdentifyService = " << i.autoIdentifyService << " autoIdentifyPassword = " << i.autoIdentifyPassword
                  << " useSasl = " << i.useSasl << " saslAccount = " << i.saslAccount << " saslPassword = " << i.saslPassword
                  << " useAutoReconnect = " << i.useAutoReconnect << " autoReconnectInterval = " << i.autoReconnectInterval
                  << " autoReconnectRetries = " << i.autoReconnectRetries << " unlimitedReconnectRetries = " << i.unlimitedReconnectRetries
                  << " rejoinChannels = " << i.rejoinChannels << " useCustomMessageRate = " << i.useCustomMessageRate
                  << " messageRateBurstSize = " << i.messageRateBurstSize << " messageRateDelay = " << i.messageRateDelay
                  << " unlimitedMessageRate = " << i.unlimitedMessageRate << ")";
    return dbg.space();
}

QDataStream& operator<<(QDataStream& out, const Network::Server& server)
{
    QVariantMap serverMap;
    serverMap["Host"] = server.host;
    serverMap["Port"] = server.port;
    serverMap["Password"] = server.password;
    serverMap["UseSSL"] = server.useSsl;
    serverMap["sslVerify"] = server.sslVerify;
    serverMap["sslVersion"] = server.sslVersion;
    serverMap["UseProxy"] = server.useProxy;
    serverMap["ProxyType"] = server.proxyType;
    serverMap["ProxyHost"] = server.proxyHost;
    serverMap["ProxyPort"] = server.proxyPort;
    serverMap["ProxyUser"] = server.proxyUser;
    serverMap["ProxyPass"] = server.proxyPass;
    out << serverMap;
    return out;
}

QDataStream& operator>>(QDataStream& in, Network::Server& server)
{
    QVariantMap serverMap;
    in >> serverMap;
    server.host = serverMap["Host"].toString();
    server.port = serverMap["Port"].toUInt();
    server.password = serverMap["Password"].toString();
    server.useSsl = serverMap["UseSSL"].toBool();
    server.sslVerify = serverMap["sslVerify"].toBool();
    server.sslVersion = serverMap["sslVersion"].toInt();
    server.useProxy = serverMap["UseProxy"].toBool();
    server.proxyType = serverMap["ProxyType"].toInt();
    server.proxyHost = serverMap["ProxyHost"].toString();
    server.proxyPort = serverMap["ProxyPort"].toUInt();
    server.proxyUser = serverMap["ProxyUser"].toString();
    server.proxyPass = serverMap["ProxyPass"].toString();
    return in;
}

bool Network::Server::operator==(const Server& other) const
{
    if (host != other.host)
        return false;
    if (port != other.port)
        return false;
    if (password != other.password)
        return false;
    if (useSsl != other.useSsl)
        return false;
    if (sslVerify != other.sslVerify)
        return false;
    if (sslVersion != other.sslVersion)
        return false;
    if (useProxy != other.useProxy)
        return false;
    if (proxyType != other.proxyType)
        return false;
    if (proxyHost != other.proxyHost)
        return false;
    if (proxyPort != other.proxyPort)
        return false;
    if (proxyUser != other.proxyUser)
        return false;
    if (proxyPass != other.proxyPass)
        return false;
    return true;
}

bool Network::Server::operator!=(const Server& other) const
{
    return !(*this == other);
}

QDebug operator<<(QDebug dbg, const Network::Server& server)
{
    dbg.nospace() << "Server(host = " << server.host << ":" << server.port << ", useSsl = " << server.useSsl
                  << ", sslVerify = " << server.sslVerify << ")";
    return dbg.space();
}
