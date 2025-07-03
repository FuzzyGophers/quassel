// SPDX-FileCopyrightText: 2005-2025 Quassel Project <devel@quassel-irc.org>
// SPDX-License-Identifier: GPL-2.0-or-later

#include "ircuser.h"

#include <QDebug>
#include <QStringConverter>
#include <QTimeZone>

#include "ircchannel.h"
#include "network.h"
#include "signalproxy.h"
#include "util.h"

IrcUser::IrcUser(const QString& hostmask, Network* network)
    : SyncableObject(network)
    , _initialized(false)
    , _nick(nickFromMask(hostmask))
    , _user(userFromMask(hostmask))
    , _host(hostFromMask(hostmask))
    , _realName()
    , _awayMessage()
    , _away(false)
    , _server()
    , _ircOperator()
    , _lastAwayMessageTime(QDateTime(QDate(1970, 1, 1), QTime(0, 0), QTimeZone::UTC))
    , _whoisServiceReply()
    , _encrypted(false)
    , _network(network)
    , _encoder(QStringConverter::Utf8)
    , _decoder(QStringConverter::Utf8)
{
    updateObjectName();
}

QString IrcUser::hostmask() const
{
    return QString("%1!%2@%3").arg(nick()).arg(user()).arg(host());
}

QDateTime IrcUser::idleTime()
{
    if ((QDateTime::currentDateTime().toMSecsSinceEpoch() - _idleTimeSet.toMSecsSinceEpoch()) > 1200000) {
        // 20 * 60 * 1000 = 1200000
        // 20 minutes have elapsed, clear the known idle time as it's likely inaccurate by now
        _idleTime = QDateTime();
    }
    return _idleTime;
}

QStringList IrcUser::channels() const
{
    QStringList chanList;
    IrcChannel* channel;
    foreach (channel, _channels) {
        chanList << channel->name();
    }
    return chanList;
}

void IrcUser::setCodecForEncoding(const QString& codecName)
{
    QStringConverter::Encoding encoding = QStringConverter::encodingForName(codecName.toUtf8().constData()).value_or(QStringConverter::Utf8);
    setCodecForEncoding(encoding);
}

void IrcUser::setCodecForEncoding(QStringConverter::Encoding encoding)
{
    _encoder = QStringEncoder(encoding);
    if (!_encoder.isValid()) {
        qWarning() << "Invalid encoding for" << QStringConverter::nameForEncoding(encoding) << ", falling back to UTF-8";
        _encoder = QStringEncoder(QStringConverter::Utf8);
    }
}

void IrcUser::setCodecForDecoding(const QString& codecName)
{
    QStringConverter::Encoding encoding = QStringConverter::encodingForName(codecName.toUtf8().constData()).value_or(QStringConverter::Utf8);
    setCodecForDecoding(encoding);
}

void IrcUser::setCodecForDecoding(QStringConverter::Encoding encoding)
{
    _decoder = QStringDecoder(encoding);
    if (!_decoder.isValid()) {
        qWarning() << "Invalid decoding for" << QStringConverter::nameForEncoding(encoding) << ", falling back to UTF-8";
        _decoder = QStringDecoder(QStringConverter::Utf8);
    }
}

QString IrcUser::decodeString(const QByteArray& text) const
{
    if (!_decoder.isValid()) {
        return network()->decodeString(text);
    }
    return ::decodeString(text, &_decoder);
}

QByteArray IrcUser::encodeString(const QString& string) const
{
    if (_encoder.isValid()) {
        return QStringEncoder(_encoder.name())(string);
    }
    return network()->encodeString(string);
}

void IrcUser::setUser(const QString& user)
{
    if (!user.isEmpty() && _user != user) {
        _user = user;
        SYNC(ARG(user));
    }
}

void IrcUser::setRealName(const QString& realName)
{
    if (!realName.isEmpty() && _realName != realName) {
        _realName = realName;
        SYNC(ARG(realName))
    }
}

void IrcUser::setAccount(const QString& account)
{
    if (_account != account) {
        _account = account;
        SYNC(ARG(account))
    }
}

void IrcUser::setAway(bool away)
{
    if (away != _away) {
        _away = away;
        markAwayChanged();
        SYNC(ARG(away))
        emit awaySet(away);
    }
}

void IrcUser::setAwayMessage(const QString& awayMessage)
{
    if (!awayMessage.isEmpty() && _awayMessage != awayMessage) {
        _awayMessage = awayMessage;
        markAwayChanged();
        SYNC(ARG(awayMessage))
    }
}

void IrcUser::setIdleTime(const QDateTime& idleTime)
{
    if (idleTime.isValid() && _idleTime != idleTime) {
        _idleTime = idleTime;
        _idleTimeSet = QDateTime::currentDateTime();
        SYNC(ARG(idleTime))
    }
}

void IrcUser::setLoginTime(const QDateTime& loginTime)
{
    if (loginTime.isValid() && _loginTime != loginTime) {
        _loginTime = loginTime;
        SYNC(ARG(loginTime))
    }
}

void IrcUser::setServer(const QString& server)
{
    if (!server.isEmpty() && _server != server) {
        _server = server;
        SYNC(ARG(server))
    }
}

void IrcUser::setIrcOperator(const QString& ircOperator)
{
    if (!ircOperator.isEmpty() && _ircOperator != ircOperator) {
        _ircOperator = ircOperator;
        SYNC(ARG(ircOperator))
    }
}

void IrcUser::setLastAwayMessage(int lastAwayMessage)
{
    QDateTime lastAwayMessageTime = QDateTime::fromSecsSinceEpoch(lastAwayMessage, QTimeZone::UTC);
    setLastAwayMessageTime(lastAwayMessageTime);
}

void IrcUser::setLastAwayMessageTime(const QDateTime& lastAwayMessageTime)
{
    if (lastAwayMessageTime.toUTC() > _lastAwayMessageTime) {
        _lastAwayMessageTime = lastAwayMessageTime.toUTC();
        SYNC(ARG(lastAwayMessageTime))
    }
}

void IrcUser::setHost(const QString& host)
{
    if (!host.isEmpty() && _host != host) {
        _host = host;
        SYNC(ARG(host))
    }
}

void IrcUser::setNick(const QString& nick)
{
    if (!nick.isEmpty() && nick != _nick) {
        _nick = nick;
        updateObjectName();
        SYNC(ARG(nick))
        emit nickSet(nick);
    }
}

void IrcUser::setWhoisServiceReply(const QString& whoisServiceReply)
{
    if (!whoisServiceReply.isEmpty() && whoisServiceReply != _whoisServiceReply) {
        _whoisServiceReply = whoisServiceReply;
        SYNC(ARG(whoisServiceReply))
    }
}

void IrcUser::setSuserHost(const QString& suserHost)
{
    if (!suserHost.isEmpty() && suserHost != _suserHost) {
        _suserHost = suserHost;
        SYNC(ARG(suserHost))
    }
}

void IrcUser::setEncrypted(bool encrypted)
{
    _encrypted = encrypted;
    emit encryptedSet(encrypted);
    SYNC(ARG(encrypted))
}

void IrcUser::updateObjectName()
{
    setObjectName(QString::number(network()->networkId().toInt()) + "/" + _nick);
}

void IrcUser::updateHostmask(const QString& mask)
{
    if (mask == hostmask())
        return;

    QString user = userFromMask(mask);
    QString host = hostFromMask(mask);
    setUser(user);
    setHost(host);
}

void IrcUser::joinChannel(IrcChannel* channel, bool skip_channel_join)
{
    Q_ASSERT(channel);
    if (!_channels.contains(channel)) {
        _channels.insert(channel);
        if (!skip_channel_join)
            channel->joinIrcUser(this);
    }
}

void IrcUser::joinChannel(const QString& channelname)
{
    joinChannel(network()->newIrcChannel(channelname));
}

void IrcUser::partChannel(IrcChannel* channel)
{
    partChannelInternal(channel, false);
}

void IrcUser::partChannel(const QString& channelname)
{
    IrcChannel* channel = network()->ircChannel(channelname);
    if (channel == nullptr) {
        qWarning() << "IrcUser::partChannel(): received part for unknown Channel" << channelname;
    }
    else {
        partChannel(channel);
    }
}

void IrcUser::partChannelInternal(IrcChannel* channel, bool skip_sync)
{
    if (_channels.contains(channel)) {
        _channels.remove(channel);
        disconnect(channel, nullptr, this, nullptr);
        channel->part(this);
        QString channelName = channel->name();
        if (!skip_sync) SYNC_OTHER(partChannel, ARG(channelName))
        if (_channels.isEmpty() && !network()->isMe(this))
            quitInternal(skip_sync);
    }
}

void IrcUser::quit()
{
    quitInternal(false);
}

void IrcUser::quitInternal(bool skip_sync)
{
    QList<IrcChannel*> channels = _channels.values();
    _channels.clear();
    foreach (IrcChannel* channel, channels) {
        disconnect(channel, nullptr, this, nullptr);
        channel->part(this);
    }
    network()->removeIrcUser(this);
    if (!skip_sync) SYNC_OTHER(quit, NO_ARG)
    emit quited();
}

void IrcUser::channelDestroyed()
{
    // private slot!
    auto* channel = static_cast<IrcChannel*>(sender());
    if (_channels.contains(channel)) {
        _channels.remove(channel);
        if (_channels.isEmpty() && !network()->isMe(this))
            quit();
    }
}

void IrcUser::setUserModes(const QString& modes)
{
    if (_userModes != modes) {
        _userModes = modes;
        SYNC(ARG(modes))
        emit userModesSet(modes);
    }
}

void IrcUser::addUserModes(const QString& modes)
{
    if (modes.isEmpty())
        return;

    bool changesMade = false;
    for (int i = 0; i < modes.size(); i++) {
        if (!_userModes.contains(modes[i])) {
            _userModes += modes[i];
            changesMade = true;
        }
    }

    if (changesMade) {
        SYNC(ARG(modes))
        emit userModesAdded(modes);
    }
}

void IrcUser::removeUserModes(const QString& modes)
{
    if (modes.isEmpty())
        return;

    for (int i = 0; i < modes.size(); i++) {
        _userModes.remove(modes[i]);
    }
    SYNC(ARG(modes))
    emit userModesRemoved(modes);
}

void IrcUser::setLastChannelActivity(BufferId buffer, const QDateTime& time)
{
    _lastActivity[buffer] = time;
    emit lastChannelActivityUpdated(buffer, time);
}

void IrcUser::setLastSpokenTo(BufferId buffer, const QDateTime& time)
{
    _lastSpokenTo[buffer] = time;
    emit lastSpokenToUpdated(buffer, time);
}
