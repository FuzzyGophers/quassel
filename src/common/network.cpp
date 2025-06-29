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

#include <QDebug>
#include <QStringConverter>
#include <QTimeZone>

#include "ircchannel.h"
#include "ircuser.h"
#include "util.h"

const QStringConverter::Encoding Network::_defaultEncoding = QStringConverter::Utf8;

Network::Network(const NetworkId& networkid, QObject* parent)
    : SyncableObject(parent)
    , _proxy(nullptr)
    , _networkId(networkid)
    , _identity(0)
    , _myNick()
    , _latency(0)
    , _networkName()
    , _currentServer()
    , _connected(false)
    , _connectionState(Disconnected)
    , _useRandomServer(false)
    , _useAutoIdentify(false)
    , _autoIdentifyService("NickServ")
    , _useSasl(false)
    , _useAutoReconnect(true)
    , _autoReconnectInterval(60)
    , _autoReconnectRetries(20)
    , _unlimitedReconnectRetries(false)
    , _rejoinChannels(true)
    , _useCustomMessageRate(false)
    , _messageRateBurstSize(5)
    , _messageRateDelay(2200)
    , _unlimitedMessageRate(false)
    , _serverEncoder(QStringConverter::Utf8)
    , _serverDecoder(QStringConverter::Utf8)
    , _encoder(QStringConverter::Utf8)
    , _decoder(QStringConverter::Utf8)
    , _autoAwayActive(false)
{
    setObjectName(QString::number(networkId().toInt()));
}

Network::~Network()
{
    emit aboutToBeDestroyed();

    // We need to delete all users and channels before we go down!
    // This gives them a chance to properly signal their destruction
    removeChansAndUsers();
}

bool Network::Server::operator==(const Server& other) const
{
    return host == other.host && port == other.port && password == other.password && useSsl == other.useSsl && sslVerify == other.sslVerify && sslVersion == other.sslVersion
           && useProxy == other.useProxy && proxyType == other.proxyType && proxyHost == other.proxyHost && proxyPort == other.proxyPort && proxyUser == other.proxyUser
           && proxyPass == other.proxyPass;
}

bool Network::Server::operator!=(const Server& other) const
{
    return !(*this == other);
}

void Network::setNetworkName(const QString& networkName)
{
    if (_networkName != networkName) {
        _networkName = networkName;
        emit networkNameSet(networkName);
        SYNC(ARG(networkName))
    }
}

void Network::setCurrentServer(const QString& currentServer)
{
    if (_currentServer != currentServer) {
        _currentServer = currentServer;
        emit currentServerSet(currentServer);
        SYNC(ARG(currentServer))
    }
}

void Network::setConnected(bool isConnected)
{
    if (_connected != isConnected) {
        _connected = isConnected;
        emit connectedSet(isConnected);
        SYNC(ARG(isConnected))
    }
}

void Network::setConnectionState(int state)
{
    if (_connectionState != state) {
        _connectionState = static_cast<ConnectionState>(state);
        emit connectionStateSet(_connectionState);
        SYNC(ARG(state))
    }
}

void Network::setMyNick(const QString& mynick)
{
    if (_myNick != mynick) {
        _myNick = mynick;
        emit myNickSet(mynick);
        SYNC(ARG(mynick))
    }
}

void Network::setLatency(int latency)
{
    if (_latency != latency) {
        _latency = latency;
        SYNC(ARG(latency))
    }
}

void Network::setIdentity(IdentityId id)
{
    if (_identity != id) {
        _identity = id;
        emit identitySet(id);
        SYNC(ARG(id))
    }
}

void Network::setServerList(const QVariantList& serverList)
{
    _serverList = fromVariantList<Server>(serverList);
    SYNC(ARG(serverList))
}

void Network::setUseRandomServer(bool useRandomServer)
{
    if (_useRandomServer != useRandomServer) {
        _useRandomServer = useRandomServer;
        SYNC(ARG(useRandomServer))
    }
}

void Network::setPerform(const QStringList& perform)
{
    if (_perform != perform) {
        _perform = perform;
        SYNC(ARG(perform))
    }
}

void Network::setSkipCaps(const QStringList& skipCaps)
{
    if (_skipCaps != skipCaps) {
        _skipCaps = skipCaps;
        _skipCaps.sort();
        SYNC(ARG(skipCaps))
    }
}

void Network::setUseAutoIdentify(bool useAutoIdentify)
{
    if (_useAutoIdentify != useAutoIdentify) {
        _useAutoIdentify = useAutoIdentify;
        SYNC(ARG(useAutoIdentify))
    }
}

void Network::setAutoIdentifyService(const QString& service)
{
    if (_autoIdentifyService != service) {
        _autoIdentifyService = service;
        SYNC(ARG(service))
    }
}

void Network::setAutoIdentifyPassword(const QString& password)
{
    if (_autoIdentifyPassword != password) {
        _autoIdentifyPassword = password;
        SYNC(ARG(password))
    }
}

void Network::setUseSasl(bool useSasl)
{
    if (_useSasl != useSasl) {
        _useSasl = useSasl;
        SYNC(ARG(useSasl))
    }
}

void Network::setSaslAccount(const QString& account)
{
    if (_saslAccount != account) {
        _saslAccount = account;
        SYNC(ARG(account))
    }
}

void Network::setSaslPassword(const QString& password)
{
    if (_saslPassword != password) {
        _saslPassword = password;
        SYNC(ARG(password))
    }
}

void Network::setUseAutoReconnect(bool useAutoReconnect)
{
    if (_useAutoReconnect != useAutoReconnect) {
        _useAutoReconnect = useAutoReconnect;
        SYNC(ARG(useAutoReconnect))
    }
}

void Network::setAutoReconnectInterval(quint32 interval)
{
    if (_autoReconnectInterval != interval) {
        _autoReconnectInterval = interval;
        SYNC(ARG(interval))
    }
}

void Network::setAutoReconnectRetries(quint16 retries)
{
    if (_autoReconnectRetries != retries) {
        _autoReconnectRetries = retries;
        SYNC(ARG(retries))
    }
}

void Network::setUnlimitedReconnectRetries(bool unlimited)
{
    if (_unlimitedReconnectRetries != unlimited) {
        _unlimitedReconnectRetries = unlimited;
        SYNC(ARG(unlimited))
    }
}

void Network::setRejoinChannels(bool rejoin)
{
    if (_rejoinChannels != rejoin) {
        _rejoinChannels = rejoin;
        SYNC(ARG(rejoin))
    }
}

void Network::setUseCustomMessageRate(bool useCustomRate)
{
    if (_useCustomMessageRate != useCustomRate) {
        _useCustomMessageRate = useCustomRate;
        emit useCustomMessageRateSet(useCustomRate);
        SYNC(ARG(useCustomRate))
    }
}

void Network::setMessageRateBurstSize(quint32 burstSize)
{
    if (_messageRateBurstSize != burstSize && burstSize >= 1) {
        _messageRateBurstSize = burstSize;
        emit messageRateBurstSizeSet(burstSize);
        SYNC(ARG(burstSize))
    }
}

void Network::setMessageRateDelay(quint32 messageDelay)
{
    if (_messageRateDelay != messageDelay) {
        _messageRateDelay = messageDelay;
        emit messageRateDelaySet(messageDelay);
        SYNC(ARG(messageDelay))
    }
}

void Network::setUnlimitedMessageRate(bool unlimitedRate)
{
    if (_unlimitedMessageRate != unlimitedRate) {
        _unlimitedMessageRate = unlimitedRate;
        emit unlimitedMessageRateSet(unlimitedRate);
        SYNC(ARG(unlimitedRate))
    }
}

void Network::addSupport(const QString& param, const QString& value)
{
    if (!_supports.contains(param) || _supports[param] != value) {
        _supports[param] = value;
        determinePrefixes();
        SYNC_OTHER(addSupport, ARG(param), ARG(value))
    }
}

void Network::removeSupport(const QString& param)
{
    if (_supports.contains(param)) {
        _supports.remove(param);
        determinePrefixes();
        SYNC_OTHER(removeSupport, ARG(param))
    }
}

void Network::addCap(const QString& capability, const QString& value)
{
    QString cap = capability.toLower();
    if (!_caps.contains(cap) || _caps[cap] != value) {
        _caps[cap] = value;
        emit capAdded(cap);
        SYNC_OTHER(addCap, ARG(capability), ARG(value))
    }
}

void Network::acknowledgeCap(const QString& capability)
{
    QString cap = capability.toLower();
    if (!_capsEnabled.contains(cap)) {
        _capsEnabled << cap;
        emit capAcknowledged(cap);
        SYNC_OTHER(acknowledgeCap, ARG(capability))
    }
}

void Network::removeCap(const QString& capability)
{
    QString cap = capability.toLower();
    if (_caps.contains(cap)) {
        _caps.remove(cap);
        _capsEnabled.removeAll(cap);
        emit capRemoved(cap);
        SYNC_OTHER(removeCap, ARG(capability))
    }
}

void Network::clearCaps()
{
    if (!_caps.isEmpty()) {
        _caps.clear();
        _capsEnabled.clear();
        SYNC_OTHER(clearCaps, NO_ARG)
    }
}

QString Network::prefixes() const
{
    determinePrefixes();
    return _prefixes;
}

QString Network::prefixModes() const
{
    determinePrefixes();
    return _prefixModes;
}

void Network::determinePrefixes() const
{
    if (_supports.contains("PREFIX")) {
        // PREFIX=(ov)@+
        QString prefix = _supports.value("PREFIX"); // (ov)@+
        int start = prefix.indexOf('(');
        int middle = prefix.indexOf(')');
        if (start >= 0 && middle > start) {
            _prefixModes = prefix.mid(start + 1, middle - start - 1);
            _prefixes = prefix.mid(middle + 1);
        }
        else {
            _prefixModes = "ov";
            _prefixes = "@+";
        }
    }
    else {
        _prefixModes = "ov";
        _prefixes = "@+";
    }
}

QString Network::prefixToMode(const QString& prefix) const
{
    QString prefixes = this->prefixes();
    QString prefixModes = this->prefixModes();
    int i = prefixes.indexOf(prefix);
    return i >= 0 && i < prefixModes.length() ? prefixModes.mid(i, 1) : QString();
}

QString Network::modeToPrefix(const QString& mode) const
{
    QString prefixes = this->prefixes();
    QString prefixModes = this->prefixModes();
    int i = prefixModes.indexOf(mode);
    return i >= 0 && i < prefixes.length() ? prefixes.mid(i, 1) : QString();
}

QString Network::sortPrefixModes(const QString& modes) const
{
    QString prefixModes = this->prefixModes();
    if (prefixModes.isEmpty()) {
        return modes;
    }

    QString sortedModes;
    // Put known modes in order of appearance in PREFIX
    for (QChar c : prefixModes) {
        if (modes.contains(c)) {
            sortedModes += c;
        }
    }
    // Then append any unknown modes
    for (QChar c : modes) {
        if (!sortedModes.contains(c)) {
            sortedModes += c;
        }
    }
    return sortedModes;
}

Network::ChannelModeType Network::channelModeType(const QString& mode)
{
    QString chanmodes = support("CHANMODES");
    QStringList modeGroups = chanmodes.split(',');
    if (modeGroups.count() != 4) {
        return NOT_A_CHANMODE;
    }

    for (int i = 0; i < mode.length(); i++) {
        if (modeGroups[0].contains(mode[i])) {
            return A_CHANMODE;
        }
        else if (modeGroups[1].contains(mode[i])) {
            return B_CHANMODE;
        }
        else if (modeGroups[2].contains(mode[i])) {
            return C_CHANMODE;
        }
        else if (modeGroups[3].contains(mode[i])) {
            return D_CHANMODE;
        }
    }
    return NOT_A_CHANMODE;
}

bool Network::isChannelName(const QString& str) const
{
    QString chantypes = support("CHANTYPES");
    if (chantypes.isEmpty())
        chantypes = "#&!+";
    if (str.isEmpty())
        return false;
    return chantypes.contains(str[0]);
}

bool Network::isStatusMsg(const QString& target) const
{
    QString statusmsg = support("STATUSMSG");
    if (statusmsg.isEmpty()) {
        statusmsg = "@+";
    }
    return target.length() >= 1 && statusmsg.contains(target[0]);
}

QString Network::support(const QString& param) const
{
    return _supports.value(param);
}

bool Network::saslMaybeSupports(const QString& saslMechanism) const
{
    if (!capAvailable(IrcCap::SASL))
        return false;

    QString mechanisms = capValue(IrcCap::SASL);
    if (mechanisms.isEmpty())
        return true; // No mechanisms advertised, assume all are possible

    return mechanisms.toUpper().split(',').contains(saslMechanism.toUpper());
}

IrcUser* Network::newIrcUser(const QString& hostmask, const QVariantMap& initData)
{
    QString nick = nickFromMask(hostmask);
    if (nick.isEmpty()) {
        return nullptr;
    }
    if (_ircUsers.contains(nick.toLower())) {
        qWarning() << QString("Trying to create duplicate IrcUser %1 on network %2").arg(nick, networkName());
        return ircUser(nick);
    }

    IrcUser* user = ircUserFactory(hostmask);
    _ircUsers[nick.toLower()] = user;
    connect(user, &IrcUser::nickSet, this, &Network::ircUserNickChanged);
    connect(user, &QObject::destroyed, this, &Network::removeIrcUser);
    user->initSet(initData);
    emit ircUserAdded(user);
    SYNC_OTHER(addIrcUser, ARG(hostmask))
    return user;
}

IrcUser* Network::ircUser(QString nickname) const
{
    return _ircUsers.value(nickname.toLower());
}

IrcChannel* Network::newIrcChannel(const QString& channelname, const QVariantMap& initData)
{
    if (_ircChannels.contains(channelname.toLower())) {
        qWarning() << QString("Trying to create duplicate IrcChannel %1 on network %2").arg(channelname, networkName());
        return ircChannel(channelname);
    }

    IrcChannel* chan = ircChannelFactory(channelname);
    _ircChannels[channelname.toLower()] = chan;
    connect(chan, &QObject::destroyed, this, &Network::removeIrcChannel);
    chan->initSet(initData);
    emit ircChannelAdded(chan);
    SYNC_OTHER(addIrcChannel, ARG(channelname))
    return chan;
}

IrcChannel* Network::ircChannel(QString channelname) const
{
    return _ircChannels.value(channelname.toLower());
}

QStringList Network::nicks() const
{
    return _ircUsers.keys();
}

void Network::ircUserNickChanged(QString newnick)
{
    IrcUser* user = qobject_cast<IrcUser*>(sender());
    if (!user)
        return;

    QString oldnick = user->nick();
    if (_ircUsers.contains(newnick.toLower())) {
        qWarning() << QString("Cannot rename IrcUser %1 to %2 on network %3: Target nick already exists!").arg(oldnick, newnick, networkName());
        return;
    }

    _ircUsers.remove(oldnick.toLower());
    _ircUsers[newnick.toLower()] = user;
}

void Network::removeIrcUser(IrcUser* ircuser)
{
    QString nick = ircuser->nick();
    _ircUsers.remove(nick.toLower());
}

void Network::removeIrcChannel(IrcChannel* ircChannel)
{
    _ircChannels.remove(ircChannel->name().toLower());
}

void Network::removeChansAndUsers()
{
    while (!_ircUsers.isEmpty()) {
        delete _ircUsers.begin().value();
    }
    while (!_ircChannels.isEmpty()) {
        delete _ircChannels.begin().value();
    }
}

QString Network::codecForServer() const
{
    return QStringConverter::nameForEncoding(QStringConverter::encodingForName(_serverEncoder.name()).value_or(_defaultEncoding));
}

QString Network::codecForEncoding() const
{
    return QStringConverter::nameForEncoding(QStringConverter::encodingForName(_encoder.name()).value_or(_defaultEncoding));
}

QString Network::codecForDecoding() const
{
    return QStringConverter::nameForEncoding(QStringConverter::encodingForName(_decoder.name()).value_or(_defaultEncoding));
}

void Network::setCodecForServer(const QString& codecName)
{
    QStringConverter::Encoding encoding = QStringConverter::encodingForName(codecName.toUtf8().constData()).value_or(_defaultEncoding);
    setCodecForServer(encoding);
}

void Network::setCodecForServer(QStringConverter::Encoding encoding)
{
    _serverEncoder = QStringEncoder(encoding);
    _serverDecoder = QStringDecoder(encoding);
    if (!_serverEncoder.isValid()) {
        qWarning() << "Invalid encoding for" << QStringConverter::nameForEncoding(encoding) << ", falling back to" << QStringConverter::nameForEncoding(_defaultEncoding);
        _serverEncoder = QStringEncoder(_defaultEncoding);
        _serverDecoder = QStringDecoder(_defaultEncoding);
    }
    SYNC_OTHER(setCodecForServer, ARG(QStringConverter::nameForEncoding(encoding)))
}

void Network::setCodecForEncoding(const QString& codecName)
{
    QStringConverter::Encoding encoding = QStringConverter::encodingForName(codecName.toUtf8().constData()).value_or(_defaultEncoding);
    setCodecForEncoding(encoding);
}

void Network::setCodecForEncoding(QStringConverter::Encoding encoding)
{
    _encoder = QStringEncoder(encoding);
    if (!_encoder.isValid()) {
        qWarning() << "Invalid encoding for" << QStringConverter::nameForEncoding(encoding) << ", falling back to" << QStringConverter::nameForEncoding(_defaultEncoding);
        _encoder = QStringEncoder(_defaultEncoding);
    }
    SYNC_OTHER(setCodecForEncoding, ARG(QStringConverter::nameForEncoding(encoding)))
}

void Network::setCodecForDecoding(const QString& codecName)
{
    QStringConverter::Encoding encoding = QStringConverter::encodingForName(codecName.toUtf8().constData()).value_or(_defaultEncoding);
    setCodecForDecoding(encoding);
}

void Network::setCodecForDecoding(QStringConverter::Encoding encoding)
{
    _decoder = QStringDecoder(encoding);
    if (!_decoder.isValid()) {
        qWarning() << "Invalid decoding for" << QStringConverter::nameForEncoding(encoding) << ", falling back to" << QStringConverter::nameForEncoding(_defaultEncoding);
        _decoder = QStringDecoder(_defaultEncoding);
    }
    SYNC_OTHER(setCodecForDecoding, ARG(QStringConverter::nameForEncoding(encoding)))
}

QString Network::decodeString(const QByteArray& text) const
{
    if (!_decoder.isValid()) {
        return decodeServerString(text);
    }
    return ::decodeString(text, &_decoder);
}

QByteArray Network::encodeString(const QString& string) const
{
    if (_encoder.isValid()) {
        return QStringEncoder(_encoder.name())(string);
    }
    return encodeServerString(string);
}

QString Network::decodeServerString(const QByteArray& text) const
{
    if (!_serverDecoder.isValid()) {
        return ::decodeString(text);
    }
    return ::decodeString(text, &_serverDecoder);
}

QByteArray Network::encodeServerString(const QString& string) const
{
    if (_serverEncoder.isValid()) {
        return QStringEncoder(_serverEncoder.name())(string);
    }
    return QStringEncoder(_defaultEncoding)(string);
}

QString Network::defaultCodecForServer()
{
    return QStringConverter::nameForEncoding(_defaultEncoding);
}

QString Network::defaultCodecForEncoding()
{
    return QStringConverter::nameForEncoding(_defaultEncoding);
}

QString Network::defaultCodecForDecoding()
{
    return QStringConverter::nameForEncoding(_defaultEncoding);
}

void Network::setDefaultCodecForServer(const QString& name)
{
    // Not implemented; would require static variable
}

void Network::setDefaultCodecForEncoding(const QString& name)
{
    // Not implemented; would require static variable
}

void Network::setDefaultCodecForDecoding(const QString& name)
{
    // Not implemented; would require static variable
}

void Network::emitConnectionError(const QString& errorMsg)
{
    emit connectionError(errorMsg);
}

NetworkInfo Network::networkInfo() const
{
    NetworkInfo info;
    info.networkName = networkName();
    info.serverList = serverList();
    info.perform = perform();
    info.skipCaps = skipCaps();
    info.autoIdentifyService = autoIdentifyService();
    info.autoIdentifyPassword = autoIdentifyPassword();
    info.saslAccount = saslAccount();
    info.saslPassword = saslPassword();
    info.codecForServer = codecForServer();
    info.codecForEncoding = codecForEncoding();
    info.codecForDecoding = codecForDecoding();
    info.networkId = networkId();
    info.identity = identity();
    info.messageRateBurstSize = messageRateBurstSize();
    info.messageRateDelay = messageRateDelay();
    info.autoReconnectInterval = autoReconnectInterval();
    info.autoReconnectRetries = autoReconnectRetries();
    info.rejoinChannels = rejoinChannels();
    info.useRandomServer = useRandomServer();
    info.useAutoIdentify = useAutoIdentify();
    info.useSasl = useSasl();
    info.useAutoReconnect = useAutoReconnect();
    info.unlimitedReconnectRetries = unlimitedReconnectRetries();
    info.useCustomMessageRate = useCustomMessageRate();
    info.unlimitedMessageRate = unlimitedMessageRate();
    return info;
}

void Network::setNetworkInfo(const NetworkInfo& networkInfo)
{
    setNetworkName(networkInfo.networkName);
    setServerList(toVariantList(networkInfo.serverList));
    setPerform(networkInfo.perform);
    setSkipCaps(networkInfo.skipCaps);
    setAutoIdentifyService(networkInfo.autoIdentifyService);
    setAutoIdentifyPassword(networkInfo.autoIdentifyPassword);
    setSaslAccount(networkInfo.saslAccount);
    setSaslPassword(networkInfo.saslPassword);
    setCodecForServer(networkInfo.codecForServer);
    setCodecForEncoding(networkInfo.codecForEncoding);
    setCodecForDecoding(networkInfo.codecForDecoding);
    setIdentity(networkInfo.identity);
    setMessageRateBurstSize(networkInfo.messageRateBurstSize);
    setMessageRateDelay(networkInfo.messageRateDelay);
    setAutoReconnectInterval(networkInfo.autoReconnectInterval);
    setAutoReconnectRetries(networkInfo.autoReconnectRetries);
    setRejoinChannels(networkInfo.rejoinChannels);
    setUseRandomServer(networkInfo.useRandomServer);
    setUseAutoIdentify(networkInfo.useAutoIdentify);
    setUseSasl(networkInfo.useSasl);
    setUseAutoReconnect(networkInfo.useAutoReconnect);
    setUnlimitedReconnectRetries(networkInfo.unlimitedReconnectRetries);
    setUseCustomMessageRate(networkInfo.useCustomMessageRate);
    setUnlimitedMessageRate(networkInfo.unlimitedMessageRate);
    emit configChanged();
}

QVariantMap Network::initSupports() const
{
    return _supports;
}

QVariantMap Network::initCaps() const
{
    return _caps;
}

void Network::initSetSupports(const QVariantMap& supports)
{
    for (QVariantMap::const_iterator iter = supports.begin(); iter != supports.end(); ++iter) {
        addSupport(iter.key(), iter.value().toString());
    }
}

void Network::initSetCaps(const QVariantMap& caps)
{
    for (QVariantMap::const_iterator iter = caps.begin(); iter != caps.end(); ++iter) {
        addCap(iter.key(), iter.value().toString());
    }
}

QVariantMap Network::initIrcUsersAndChannels() const
{
    QVariantMap usersAndChannels;

    QVariantMap users;
    foreach (IrcUser* user, _ircUsers) {
        users[user->nick()] = user->toVariantMap();
    }
    usersAndChannels["IrcUsers"] = users;

    QVariantMap channels;
    foreach (IrcChannel* channel, _ircChannels) {
        channels[channel->name()] = channel->toVariantMap();
    }
    usersAndChannels["IrcChannels"] = channels;

    return usersAndChannels;
}

void Network::initSetIrcUsersAndChannels(const QVariantMap& usersAndChannels)
{
    QVariantMap users = usersAndChannels["IrcUsers"].toMap();
    for (QVariantMap::const_iterator iter = users.begin(); iter != users.end(); ++iter) {
        newIrcUser(iter.key(), iter.value().toMap());
    }

    QVariantMap channels = usersAndChannels["IrcChannels"].toMap();
    for (QVariantMap::const_iterator iter = channels.begin(); iter != channels.end(); ++iter) {
        newIrcChannel(iter.key(), iter.value().toMap());
    }
}

IrcUser* Network::updateNickFromMask(const QString& mask)
{
    QString nick = nickFromMask(mask);
    if (nick.isEmpty()) {
        return nullptr;
    }

    IrcUser* user = ircUser(nick);
    if (!user) {
        return newIrcUser(mask);
    }
    user->updateHostmask(mask);
    return user;
}

bool NetworkInfo::operator==(const NetworkInfo& other) const
{
    return networkName == other.networkName && serverList == other.serverList && perform == other.perform && skipCaps == other.skipCaps
           && autoIdentifyService == other.autoIdentifyService && autoIdentifyPassword == other.autoIdentifyPassword && saslAccount == other.saslAccount
           && saslPassword == other.saslPassword && codecForServer == other.codecForServer && codecForEncoding == other.codecForEncoding
           && codecForDecoding == other.codecForDecoding && networkId == other.networkId && identity == other.identity
           && messageRateBurstSize == other.messageRateBurstSize && messageRateDelay == other.messageRateDelay
           && autoReconnectInterval == other.autoReconnectInterval && autoReconnectRetries == other.autoReconnectRetries
           && rejoinChannels == other.rejoinChannels && useRandomServer == other.useRandomServer && useAutoIdentify == other.useAutoIdentify
           && useSasl == other.useSasl && useAutoReconnect == other.useAutoReconnect && unlimitedReconnectRetries == other.unlimitedReconnectRetries
           && useCustomMessageRate == other.useCustomMessageRate && unlimitedMessageRate == other.unlimitedMessageRate;
}

bool NetworkInfo::operator!=(const NetworkInfo& other) const
{
    return !(*this == other);
}

QString NetworkInfo::skipCapsToString() const
{
    return skipCaps.join(" ");
}

void NetworkInfo::skipCapsFromString(const QString& flattenedSkipCaps)
{
    skipCaps = flattenedSkipCaps.split(" ", Qt::SkipEmptyParts);
}

QDataStream& operator<<(QDataStream& out, const NetworkInfo& info)
{
    out << info.networkName << info.serverList << info.perform << info.skipCaps << info.autoIdentifyService << info.autoIdentifyPassword << info.saslAccount
        << info.saslPassword << info.codecForServer << info.codecForEncoding << info.codecForDecoding << info.networkId << info.identity
        << info.messageRateBurstSize << info.messageRateDelay << info.autoReconnectInterval << info.autoReconnectRetries << info.rejoinChannels
        << info.useRandomServer << info.useAutoIdentify << info.useSasl << info.useAutoReconnect << info.unlimitedReconnectRetries << info.useCustomMessageRate
        << info.unlimitedMessageRate;
    return out;
}

QDataStream& operator>>(QDataStream& in, NetworkInfo& info)
{
    in >> info.networkName >> info.serverList >> info.perform >> info.skipCaps >> info.autoIdentifyService >> info.autoIdentifyPassword >> info.saslAccount
        >> info.saslPassword >> info.codecForServer >> info.codecForEncoding >> info.codecForDecoding >> info.networkId >> info.identity
        >> info.messageRateBurstSize >> info.messageRateDelay >> info.autoReconnectInterval >> info.autoReconnectRetries >> info.rejoinChannels
        >> info.useRandomServer >> info.useAutoIdentify >> info.useSasl >> info.useAutoReconnect >> info.unlimitedReconnectRetries >> info.useCustomMessageRate
        >> info.unlimitedMessageRate;
    return in;
}

QDebug operator<<(QDebug dbg, const NetworkInfo& i)
{
    dbg.nospace() << "NetworkInfo(Network: " << qPrintable(i.networkName) << ", Id: " << i.networkId << ")";
    return dbg.space();
}

QDataStream& operator<<(QDataStream& out, const Network::Server& server)
{
    out << server.host << server.port << server.password << server.useSsl << server.sslVerify << server.sslVersion << server.useProxy << server.proxyType
        << server.proxyHost << server.proxyPort << server.proxyUser << server.proxyPass;
    return out;
}

QDataStream& operator>>(QDataStream& in, Network::Server& server)
{
    in >> server.host >> server.port >> server.password >> server.useSsl >> server.sslVerify >> server.sslVersion >> server.useProxy >> server.proxyType
        >> server.proxyHost >> server.proxyPort >> server.proxyUser >> server.proxyPass;
    return in;
}

QDebug operator<<(QDebug dbg, const Network::Server& server)
{
    dbg.nospace() << "Server(" << qPrintable(server.host) << ":" << server.port << (server.useSsl ? ", SSL" : "") << ")";
    return dbg.space();
}
