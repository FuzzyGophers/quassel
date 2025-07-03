// SPDX-FileCopyrightText: 2005-2025 Quassel Project <devel@quassel-irc.org>
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

#include "common-export.h"

#include "types.h"

class QString;
class QDataStream;

class COMMON_EXPORT BufferInfo
{
public:
    enum Type
    {
        InvalidBuffer = 0x00,
        StatusBuffer = 0x01,
        ChannelBuffer = 0x02,
        QueryBuffer = 0x04,
        GroupBuffer = 0x08
    };

    enum Activity
    {
        NoActivity = 0x00,
        OtherActivity = 0x01,
        NewMessage = 0x02,
        Highlight = 0x40
    };
    Q_DECLARE_FLAGS(ActivityLevel, Activity)

    BufferInfo();
    BufferInfo(BufferId id, NetworkId networkid, Type type, uint gid = 0, QString buf = QString());

    static BufferInfo fakeStatusBuffer(NetworkId networkId);

    inline bool isValid() const { return _bufferId != 0; }
    inline const BufferId& bufferId() const { return _bufferId; }
    inline void setBufferId(BufferId id) { _bufferId = id; }
    inline const NetworkId& networkId() const { return _netid; }
    inline const Type& type() const { return _type; }
    inline const uint& groupId() const { return _groupId; }
    void setGroupId(uint gid) { _groupId = gid; }

    QString bufferName() const;
    bool acceptsRegularMessages() const;

    inline bool operator==(const BufferInfo& other) const { return _bufferId == other._bufferId; }

private:
    BufferId _bufferId;
    NetworkId _netid;
    Type _type{InvalidBuffer};
    uint _groupId{0};
    QString _bufferName;

    friend uint qHash(const BufferInfo&);
    friend QDataStream& operator<<(QDataStream& out, const BufferInfo& bufferInfo);
    friend QDataStream& operator>>(QDataStream& in, BufferInfo& bufferInfo);
};

QDataStream& operator<<(QDataStream& out, const BufferInfo& bufferInfo);
QDataStream& operator>>(QDataStream& in, BufferInfo& bufferInfo);
QDebug operator<<(QDebug dbg, const BufferInfo& b);

Q_DECLARE_METATYPE(BufferInfo)
Q_DECLARE_OPERATORS_FOR_FLAGS(BufferInfo::ActivityLevel)

uint qHash(const BufferInfo&);
