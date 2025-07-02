// SPDX-License-Identifier: GPL-2.0-or-later

#include "ircevent.h"

Event* IrcEvent::create(EventManager::EventType type, QVariantMap& map, Network* network)
{
    if ((type & ~EventManager::IrcEventNumericMask) == EventManager::IrcEventNumeric)
        return new IrcEventNumeric(type, map, network);

    if ((type & EventManager::EventGroupMask) != EventManager::IrcEvent)
        return nullptr;

    switch (type) {
    case EventManager::IrcEventRawPrivmsg:
    case EventManager::IrcEventRawNotice:
        return new IrcEventRawMessage(type, map, network);

    default:
        return new IrcEvent(type, map, network);
    }
}

IrcEvent::IrcEvent(EventManager::EventType type, QVariantMap& map, Network* network)
    : NetworkEvent(type, map, network)
{
    _prefix = map.take("prefix").toString();
    _params = map.take("params").toStringList();
}

void IrcEvent::toVariantMap(QVariantMap& map) const
{
    NetworkEvent::toVariantMap(map);
    map["prefix"] = prefix();
    map["params"] = params();
}

IrcEventNumeric::IrcEventNumeric(EventManager::EventType type, QVariantMap& map, Network* network)
    : IrcEvent(type, map, network)
{
    _number = map.take("number").toUInt();
    _target = map.take("target").toString();
}

void IrcEventNumeric::toVariantMap(QVariantMap& map) const
{
    IrcEvent::toVariantMap(map);
    map["number"] = number();
    map["target"] = target();
}

IrcEventRawMessage::IrcEventRawMessage(EventManager::EventType type, QVariantMap& map, Network* network)
    : IrcEvent(type, map, network)
{
    _rawMessage = map.take("rawMessage").toByteArray();
}

void IrcEventRawMessage::toVariantMap(QVariantMap& map) const
{
    IrcEvent::toVariantMap(map);
    map["rawMessage"] = rawMessage();
}
