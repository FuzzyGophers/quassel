// SPDX-License-Identifier: GPL-2.0-or-later

#include "keyevent.h"

Event* KeyEvent::create(EventManager::EventType type, QVariantMap& map, Network* network)
{
    if (type == EventManager::KeyEvent)
        return new KeyEvent(type, map, network);

    return nullptr;
}

KeyEvent::KeyEvent(EventManager::EventType type, QVariantMap& map, Network* network)
    : IrcEvent(type, map, network)
{
    _exchangeType = static_cast<ExchangeType>(map.take("exchangeType").toInt());
    _target = map.take("target").toString();
    _key = map.take("key").toByteArray();
}

void KeyEvent::toVariantMap(QVariantMap& map) const
{
    IrcEvent::toVariantMap(map);
    map["exchangeType"] = exchangeType();
    map["target"] = target();
    map["key"] = key();
}
