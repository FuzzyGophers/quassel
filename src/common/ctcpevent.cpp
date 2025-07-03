// SPDX-FileCopyrightText: 2005-2025 Quassel Project <devel@quassel-irc.org>
// SPDX-License-Identifier: GPL-2.0-or-later

#include "ctcpevent.h"

Event* CtcpEvent::create(EventManager::EventType type, QVariantMap& map, Network* network)
{
    if (type == EventManager::CtcpEvent || type == EventManager::CtcpEventFlush)
        return new CtcpEvent(type, map, network);

    return nullptr;
}

CtcpEvent::CtcpEvent(EventManager::EventType type, QVariantMap& map, Network* network)
    : IrcEvent(type, map, network)
{
    _ctcpType = static_cast<CtcpType>(map.take("ctcpType").toInt());
    _ctcpCmd = map.take("ctcpCmd").toString();
    _target = map.take("target").toString();
    _param = map.take("param").toString();
    _reply = map.take("reply").toString();
    _uuid = QUuid::fromString(map.take("uuid").toString());
}

void CtcpEvent::toVariantMap(QVariantMap& map) const
{
    IrcEvent::toVariantMap(map);
    map["ctcpType"] = static_cast<int>(ctcpType());
    map["ctcpCmd"] = ctcpCmd();
    map["target"] = target();
    map["param"] = param();
    map["reply"] = reply();
    map["uuid"] = uuid().toString();
}
