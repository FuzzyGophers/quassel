// SPDX-FileCopyrightText: 2005-2025 Quassel Project <devel@quassel-irc.org>
// SPDX-License-Identifier: GPL-2.0-or-later

#include "bufferinfo.h"

#include <utility>

#include <QByteArray>
#include <QDataStream>
#include <QDebug>
#include <QString>

#include "util.h"

BufferInfo::BufferInfo()
    : _bufferId(0)
    , _netid(0)
    , _bufferName(QString())
{
}

BufferInfo::BufferInfo(BufferId id, NetworkId networkid, Type type, uint gid, QString buf)
    : _bufferId(id)
    , _netid(networkid)
    , _type(type)
    , _groupId(gid)
    , _bufferName(std::move(buf))
{
}

BufferInfo BufferInfo::fakeStatusBuffer(NetworkId networkId)
{
    return BufferInfo(0, networkId, StatusBuffer);
}

QString BufferInfo::bufferName() const
{
    if (isChannelName(_bufferName))
        return _bufferName;
    else
        return nickFromMask(_bufferName);  // FIXME get rid of global functions and use the Network stuff instead!
}

bool BufferInfo::acceptsRegularMessages() const
{
    if (_type == StatusBuffer || _type == InvalidBuffer)
        return false;
    return true;
}

QDebug operator<<(QDebug dbg, const BufferInfo& b)
{
    dbg.nospace() << "(bufId: " << b.bufferId() << ", netId: " << b.networkId() << ", groupId: " << b.groupId()
                  << ", buf: " << b.bufferName() << ")";
    return dbg.space();
}

QDataStream& operator<<(QDataStream& out, const BufferInfo& bufferInfo)
{
    out << bufferInfo._bufferId << bufferInfo._netid << (qint16)bufferInfo._type << bufferInfo._groupId << bufferInfo._bufferName.toUtf8();
    return out;
}

QDataStream& operator>>(QDataStream& in, BufferInfo& bufferInfo)
{
    QByteArray buffername;
    qint16 bufferType;
    in >> bufferInfo._bufferId >> bufferInfo._netid >> bufferType >> bufferInfo._groupId >> buffername;
    bufferInfo._type = (BufferInfo::Type)bufferType;
    bufferInfo._bufferName = QString::fromUtf8(buffername);
    return in;
}

uint qHash(const BufferInfo& bufferid)
{
    return qHash(bufferid._bufferId);
}
