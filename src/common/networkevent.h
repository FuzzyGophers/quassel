// SPDX-FileCopyrightText: 2005-2025 Quassel Project <devel@quassel-irc.org>
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

#include <utility>

#include <QStringList>
#include <QVariantList>

#include "event.h"
#include "network.h"

class COMMON_EXPORT NetworkEvent : public Event
{
public:
    explicit NetworkEvent(EventManager::EventType type, Network* network)
        : Event(type)
        , _network(network)
    {
    }

    inline NetworkId networkId() const { return network() ? network()->networkId() : NetworkId(); }
    inline Network* network() const { return _network; }

    static Event* create(EventManager::EventType type, QVariantMap& map, Network* network);

protected:
    explicit NetworkEvent(EventManager::EventType type, QVariantMap& map, Network* network);
    void toVariantMap(QVariantMap& map) const override;

    inline QString className() const override { return "NetworkEvent"; }
    inline void debugInfo(QDebug& dbg) const override { dbg.nospace() << ", net = " << qPrintable(_network->networkName()); }

private:
    Network* _network;
};

/*****************************************************************************/

class COMMON_EXPORT NetworkConnectionEvent : public NetworkEvent
{
public:
    explicit NetworkConnectionEvent(EventManager::EventType type, Network* network, Network::ConnectionState state)
        : NetworkEvent(type, network)
        , _state(state)
    {
    }

    inline Network::ConnectionState connectionState() const { return _state; }
    inline void setConnectionState(Network::ConnectionState state) { _state = state; }

protected:
    explicit NetworkConnectionEvent(EventManager::EventType type, QVariantMap& map, Network* network);
    void toVariantMap(QVariantMap& map) const override;

    inline QString className() const override { return "NetworkConnectionEvent"; }
    inline void debugInfo(QDebug& dbg) const override
    {
        NetworkEvent::debugInfo(dbg);
        dbg.nospace() << ", state = " << qPrintable(QString::number(_state));
    }

private:
    Network::ConnectionState _state;

    friend class NetworkEvent;
};

class COMMON_EXPORT NetworkDataEvent : public NetworkEvent
{
public:
    explicit NetworkDataEvent(EventManager::EventType type, Network* network, QByteArray data)
        : NetworkEvent(type, network)
        , _data(std::move(data))
    {
    }

    inline QByteArray data() const { return _data; }
    inline void setData(const QByteArray& data) { _data = data; }

protected:
    explicit NetworkDataEvent(EventManager::EventType type, QVariantMap& map, Network* network);
    void toVariantMap(QVariantMap& map) const override;

    inline QString className() const override { return "NetworkDataEvent"; }
    inline void debugInfo(QDebug& dbg) const override
    {
        NetworkEvent::debugInfo(dbg);
        dbg.nospace() << ", data = " << data();
    }

private:
    QByteArray _data;

    friend class NetworkEvent;
};

class COMMON_EXPORT NetworkSplitEvent : public NetworkEvent
{
public:
    explicit NetworkSplitEvent(EventManager::EventType type, Network* network, QString channel, QStringList users, QString quitMsg)
        : NetworkEvent(type, network)
        , _channel(std::move(channel))
        , _users(std::move(users))
        , _quitMsg(std::move(quitMsg))
    {
    }

    inline QString channel() const { return _channel; }
    inline QStringList users() const { return _users; }
    inline QString quitMessage() const { return _quitMsg; }

protected:
    explicit NetworkSplitEvent(EventManager::EventType type, QVariantMap& map, Network* network);
    void toVariantMap(QVariantMap& map) const override;

    inline QString className() const override { return "NetworkSplitEvent"; }
    inline void debugInfo(QDebug& dbg) const override
    {
        NetworkEvent::debugInfo(dbg);
        dbg.nospace() << ", channel = " << qPrintable(channel()) << ", users = " << users() << ", quitmsg = " << quitMessage();
    }

private:
    QString _channel;
    QStringList _users;
    QString _quitMsg;

    friend class NetworkEvent;
};
