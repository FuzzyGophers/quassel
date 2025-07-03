// SPDX-FileCopyrightText: 2005-2025 Quassel Project <devel@quassel-irc.org>
// SPDX-License-Identifier: GPL-2.0-or-later

#include "ctcpevent.h"
#include "ircevent.h"
#include "messageevent.h"
#include "networkevent.h"
#include "peer.h"
#include "signalproxy.h"

Event::Event(EventManager::EventType type)
    : _type(type)
{
}

Event::Event(EventManager::EventType type, QVariantMap& map)
    : _type(type)
{
    if (!map.contains("flags") || !map.contains("timestamp")) {
        qWarning() << "Received invalid serialized event:" << map;
        setValid(false);
        return;
    }

    Q_ASSERT(SignalProxy::current());
    Q_ASSERT(SignalProxy::current()->sourcePeer());

    setFlags(static_cast<EventManager::EventFlags>(map.take("flags").toInt()));  // TODO sanity check?

    if (SignalProxy::current()->sourcePeer()->hasFeature(Quassel::Feature::LongTime)) {
        // timestamp is a qint64
        setTimestamp(QDateTime::fromMSecsSinceEpoch(map.take("timestamp").toLongLong()));
    }
    else {
        // timestamp is a quint32
        setTimestamp(QDateTime::fromSecsSinceEpoch(map.take("timestamp").toUInt()));
    }
}

void Event::toVariantMap(QVariantMap& map) const
{
    Q_ASSERT(SignalProxy::current());
    Q_ASSERT(SignalProxy::current()->targetPeer());

    map["type"] = static_cast<int>(type());
    map["flags"] = static_cast<int>(flags());
    if (SignalProxy::current()->targetPeer()->hasFeature(Quassel::Feature::LongTime)) {
        // toMSecsSinceEpoch returns a qint64
        map["timestamp"] = timestamp().toMSecsSinceEpoch();
    }
    else {
        // toSecsSinceEpoch returns a qint64, cast to quint32 for compatibility
        map["timestamp"] = static_cast<quint32>(timestamp().toSecsSinceEpoch());
    }
}

QVariantMap Event::toVariantMap() const
{
    QVariantMap map;
    toVariantMap(map);
    return map;
}

Event* Event::fromVariantMap(QVariantMap& map, Network* network)
{
    int inttype = map.take("type").toInt();
    // sanity check if we have a valid enum value
    if (EventManager::enumName(inttype).isEmpty()) {
        qWarning() << "Received a serialized event with unknown type" << inttype;
        return nullptr;
    }

    auto type = static_cast<EventManager::EventType>(inttype);
    if (type == EventManager::Invalid || type == EventManager::GenericEvent)
        return nullptr;

    auto group = static_cast<EventManager::EventType>(type & EventManager::EventGroupMask);

    Event* e = nullptr;

    // we use static create() functions to keep group-specific special cases in the files they belong
    // e.g. IrcEventRawMessage
    switch (group) {
    case EventManager::NetworkEvent:
        e = NetworkEvent::create(type, map, network);
        break;
    case EventManager::IrcServerEvent:
        // not in use!
        break;
    case EventManager::IrcEvent:
        e = IrcEvent::create(type, map, network);
        break;
    case EventManager::MessageEvent:
        e = MessageEvent::create(type, map, network);
        break;
    case EventManager::CtcpEvent:
        e = CtcpEvent::create(type, map, network);
        break;
    default:
        break;
    }

    if (!e) {
        qWarning() << "Can't create event of type" << type;
        return nullptr;
    }

    if (!map.isEmpty()) {
        qWarning() << "Event creation from map did not consume all data:" << map;
    }

    return e;
}

QDebug operator<<(QDebug dbg, Event* e)
{
    dbg.nospace() << qPrintable(e->className()) << "("
                  << "type = 0x" << qPrintable(QString::number(e->type(), 16));
    e->debugInfo(dbg);
    //<< ", data = " << e->data(); // we don't use data anywhere yet
    dbg.nospace() << ", flags = 0x" << qPrintable(QString::number(e->flags(), 16)) << ")";
    return dbg.space();
}
