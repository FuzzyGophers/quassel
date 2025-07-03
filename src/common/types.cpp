// SPDX-FileCopyrightText: 2005-2025 Quassel Project <devel@quassel-irc.org>
// SPDX-License-Identifier: GPL-2.0-or-later

#include "types.h"

#include "peer.h"

QDataStream& operator<<(QDataStream& out, const SignedId64& signedId)
{
    Q_ASSERT(SignalProxy::current());
    Q_ASSERT(SignalProxy::current()->targetPeer());

    if (SignalProxy::current()->targetPeer()->hasFeature(Quassel::Feature::LongMessageId)) {
        out << signedId.toQint64();
    }
    else {
        out << (qint32)signedId.toQint64();
    }
    return out;
}

QDataStream& operator>>(QDataStream& in, SignedId64& signedId)
{
    Q_ASSERT(SignalProxy::current());
    Q_ASSERT(SignalProxy::current()->sourcePeer());

    if (SignalProxy::current()->sourcePeer()->hasFeature(Quassel::Feature::LongMessageId)) {
        in >> signedId.id;
    }
    else {
        qint32 id;
        in >> id;
        signedId.id = id;
    }
    return in;
}
