// SPDX-FileCopyrightText: 2005-2025 Quassel Project <devel@quassel-irc.org>
// SPDX-License-Identifier: GPL-2.0-or-later

#include "messageevent.h"

#include <utility>

Event* MessageEvent::create(EventManager::EventType type, QVariantMap& map, Network* network)
{
    if (type == EventManager::MessageEvent)
        return new MessageEvent(type, map, network);

    return nullptr;
}

MessageEvent::MessageEvent(
    Message::Type msgType, Network* net, QString msg, QString sender, QString target, Message::Flags flags, const QDateTime& timestamp)
    : NetworkEvent(EventManager::MessageEvent, net)
    , _msgType(msgType)
    , _text(std::move(msg))
    , _sender(std::move(sender))
    , _target(std::move(target))
    , _msgFlags(flags)
{
    IrcChannel* channel = network()->ircChannel(_target);
    if (!channel) {
        if (!_target.isEmpty() && network()->prefixes().contains(_target.at(0)))
            _target = _target.mid(1);

        if (_target.startsWith('$') || _target.startsWith('#'))
            _target = nickFromMask(_sender);
    }

    _bufferType = bufferTypeByTarget(_target);

    if (timestamp.isValid())
        setTimestamp(timestamp);
    else
        setTimestamp(QDateTime::currentDateTime());
}

MessageEvent::MessageEvent(EventManager::EventType type, QVariantMap& map, Network* network)
    : NetworkEvent(type, map, network)
{
    _msgType = static_cast<Message::Type>(map.take("messageType").toInt());
    _msgFlags = static_cast<Message::Flags>(map.take("messageFlags").toInt());
    _bufferType = static_cast<BufferInfo::Type>(map.take("bufferType").toInt());
    _text = map.take("text").toString();
    _sender = map.take("sender").toString();
    _target = map.take("target").toString();
}

void MessageEvent::toVariantMap(QVariantMap& map) const
{
    NetworkEvent::toVariantMap(map);
    map["messageType"] = msgType();
    map["messageFlags"] = (int)msgFlags();
    map["bufferType"] = bufferType();
    map["text"] = text();
    map["sender"] = sender();
    map["target"] = target();
}

BufferInfo::Type MessageEvent::bufferTypeByTarget(const QString& target) const
{
    if (target.isEmpty())
        return BufferInfo::StatusBuffer;

    if (network()->isChannelName(target))
        return BufferInfo::ChannelBuffer;

    return BufferInfo::QueryBuffer;
}
