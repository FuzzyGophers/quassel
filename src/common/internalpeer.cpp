// SPDX-FileCopyrightText: 2005-2025 Quassel Project <devel@quassel-irc.org>
// SPDX-License-Identifier: GPL-2.0-or-later

#include "internalpeer.h"

#include "util.h"

using namespace QuasselProtocol;

InternalPeer::InternalPeer(QObject* parent)
    : Peer(nullptr, parent)
{
    static bool registered = []() {
        qRegisterMetaType<QPointer<InternalPeer>>();
        qRegisterMetaType<QuasselProtocol::SyncMessage>();
        qRegisterMetaType<QuasselProtocol::RpcCall>();
        qRegisterMetaType<QuasselProtocol::InitRequest>();
        qRegisterMetaType<QuasselProtocol::InitData>();
        return true;
    }();
    Q_UNUSED(registered)

    setFeatures(Quassel::Features{});
}

InternalPeer::~InternalPeer()
{
    if (_isOpen) {
        emit disconnected();
    }
}

QString InternalPeer::description() const
{
    return tr("internal connection");
}

QString InternalPeer::address() const
{
    return tr("internal connection");
}

quint16 InternalPeer::port() const
{
    return 0;
}

bool InternalPeer::isOpen() const
{
    return _isOpen;
}

bool InternalPeer::isSecure() const
{
    return true;
}

bool InternalPeer::isLocal() const
{
    return true;
}

void InternalPeer::close(const QString& reason)
{
    Q_UNUSED(reason);
    _isOpen = false;
}

int InternalPeer::lag() const
{
    return 0;
}

::SignalProxy* InternalPeer::signalProxy() const
{
    return _proxy;
}

void InternalPeer::setSignalProxy(::SignalProxy* proxy)
{
    if (!proxy && _proxy) {
        _proxy = nullptr;
        if (_isOpen) {
            _isOpen = false;
            emit disconnected();
        }
        return;
    }

    if (proxy && !_proxy) {
        _proxy = proxy;
        _isOpen = true;
        return;
    }

    qWarning() << Q_FUNC_INFO << "Changing the SignalProxy is not supported!";
}

void InternalPeer::setPeer(InternalPeer* peer)
{
    connect(peer,
            selectOverload<const QuasselProtocol::SyncMessage&>(&InternalPeer::dispatchMessage),
            this,
            selectOverload<const QuasselProtocol::SyncMessage&>(&InternalPeer::handleMessage));
    connect(peer,
            selectOverload<const QuasselProtocol::RpcCall&>(&InternalPeer::dispatchMessage),
            this,
            selectOverload<const QuasselProtocol::RpcCall&>(&InternalPeer::handleMessage));
    connect(peer,
            selectOverload<const QuasselProtocol::InitRequest&>(&InternalPeer::dispatchMessage),
            this,
            selectOverload<const QuasselProtocol::InitRequest&>(&InternalPeer::handleMessage));
    connect(peer,
            selectOverload<const QuasselProtocol::InitData&>(&InternalPeer::dispatchMessage),
            this,
            selectOverload<const QuasselProtocol::InitData&>(&InternalPeer::handleMessage));

    connect(peer, &Peer::disconnected, this, &InternalPeer::peerDisconnected);

    _isOpen = true;
}

void InternalPeer::peerDisconnected()
{
    disconnect(sender(), nullptr, this, nullptr);
    if (_isOpen) {
        _isOpen = false;
        emit disconnected();
    }
}

void InternalPeer::dispatch(const SyncMessage& msg)
{
    emit dispatchMessage(msg);
}

void InternalPeer::dispatch(const RpcCall& msg)
{
    emit dispatchMessage(msg);
}

void InternalPeer::dispatch(const InitRequest& msg)
{
    emit dispatchMessage(msg);
}

void InternalPeer::dispatch(const InitData& msg)
{
    emit dispatchMessage(msg);
}

void InternalPeer::handleMessage(const QuasselProtocol::SyncMessage& msg)
{
    handle(msg);
}

void InternalPeer::handleMessage(const QuasselProtocol::RpcCall& msg)
{
    handle(msg);
}

void InternalPeer::handleMessage(const QuasselProtocol::InitRequest& msg)
{
    handle(msg);
}

void InternalPeer::handleMessage(const QuasselProtocol::InitData& msg)
{
    handle(msg);
}

template<class T>
void InternalPeer::handle(const T& msg)
{
    static auto setSourcePeer = [](Peer* peer) {
        auto p = SignalProxy::current();
        if (p) {
            p->setSourcePeer(peer);
        }
    };

    setSourcePeer(this);
    Peer::handle(msg);
    setSourcePeer(nullptr);
}
