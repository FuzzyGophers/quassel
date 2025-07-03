// SPDX-FileCopyrightText: 2005-2025 Quassel Project <devel@quassel-irc.org>
// SPDX-License-Identifier: GPL-2.0-or-later

#include "peer.h"

Peer::Peer(AuthHandler* authHandler, QObject* parent)
    : QObject(parent)
    , _authHandler(authHandler)
{
}

AuthHandler* Peer::authHandler() const
{
    return _authHandler;
}

QDateTime Peer::connectedSince() const
{
    return _connectedSince;
}

void Peer::setConnectedSince(const QDateTime& connectedSince)
{
    _connectedSince = connectedSince;
}

QString Peer::buildDate() const
{
    return _buildDate;
}

void Peer::setBuildDate(const QString& buildDate)
{
    _buildDate = buildDate;
}

QString Peer::clientVersion() const
{
    return _clientVersion;
}

void Peer::setClientVersion(const QString& clientVersion)
{
    _clientVersion = clientVersion;
}

bool Peer::hasFeature(Quassel::Feature feature) const
{
    return _features.isEnabled(feature);
}

Quassel::Features Peer::features() const
{
    return _features;
}

void Peer::setFeatures(Quassel::Features features)
{
    _features = std::move(features);
}

int Peer::id() const
{
    return _id;
}

void Peer::setId(int id)
{
    _id = id;
}

// PeerPtr is used in RPC signatures for enabling receivers to send replies
// to a particular peer rather than broadcast to all connected ones.
// To enable this, the SignalProxy transparently replaces the bogus value
// received over the network with the actual address of the local Peer
// instance. Because the actual value isn't needed on the wire, it is
// serialized as null.
QDataStream& operator<<(QDataStream& out, PeerPtr ptr)
{
    Q_UNUSED(ptr);
    out << static_cast<quint64>(0);  // 64 bit for historic reasons
    return out;
}

QDataStream& operator>>(QDataStream& in, PeerPtr& ptr)
{
    ptr = nullptr;
    quint64 value;
    in >> value;
    return in;
}
