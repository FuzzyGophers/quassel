// SPDX-FileCopyrightText: 2005-2025 Quassel Project <devel@quassel-irc.org>
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

#include "common-export.h"

#include <QCoreApplication>
#include <QDateTime>

#include "bufferinfo.h"
#include "types.h"

class COMMON_EXPORT Message
{
    Q_DECLARE_TR_FUNCTIONS(Message)

public:
    /** The different types a message can have for display */
    enum Type
    {
        Plain = 0x00001,
        Notice = 0x00002,
        Action = 0x00004,
        Nick = 0x00008,
        Mode = 0x00010,
        Join = 0x00020,
        Part = 0x00040,
        Quit = 0x00080,
        Kick = 0x00100,
        Kill = 0x00200,
        Server = 0x00400,
        Info = 0x00800,
        Error = 0x01000,
        DayChange = 0x02000,
        Topic = 0x04000,
        NetsplitJoin = 0x08000,
        NetsplitQuit = 0x10000,
        Invite = 0x20000,
    };
    Q_DECLARE_FLAGS(Types, Type)

    // DO NOT CHANGE without knowing what you do, some of these flags are stored in the database
    enum Flag
    {
        None = 0x00,
        Self = 0x01,
        Highlight = 0x02,
        Redirected = 0x04,
        ServerMsg = 0x08,
        StatusMsg = 0x10,
        Ignored = 0x20,  ///< This message matched an active ignore rule when first received
        Backlog = 0x80
    };
    Q_DECLARE_FLAGS(Flags, Flag)

    Message(BufferInfo bufferInfo = BufferInfo(),
            Type type = Plain,
            QString contents = {},
            QString sender = {},
            QString senderPrefixes = {},
            QString realName = {},
            QString avatarUrl = {},
            Flags flags = None);
    Message(QDateTime ts,
            BufferInfo buffer = BufferInfo(),
            Type type = Plain,
            QString contents = {},
            QString sender = {},
            QString senderPrefixes = {},
            QString realName = {},
            QString avatarUrl = {},
            Flags flags = None);

    inline static Message ChangeOfDay(const QDateTime& day) { return Message(day, BufferInfo(), DayChange); }
    inline const MsgId& msgId() const { return _msgId; }
    inline void setMsgId(MsgId id) { _msgId = id; }

    inline const BufferInfo& bufferInfo() const { return _bufferInfo; }
    inline const BufferId& bufferId() const { return _bufferInfo.bufferId(); }
    inline void setBufferId(BufferId id) { _bufferInfo.setBufferId(id); }
    inline const QString& contents() const { return _contents; }
    inline const QString& sender() const { return _sender; }
    inline const QString& senderPrefixes() const { return _senderPrefixes; }
    inline const QString& realName() const { return _realName; }
    inline const QString& avatarUrl() const { return _avatarUrl; }
    inline Type type() const { return _type; }
    inline Flags flags() const { return _flags; }
    inline void setFlags(Flags flags) { _flags = flags; }
    inline const QDateTime& timestamp() const { return _timestamp; }

    inline bool isValid() const { return _msgId.isValid(); }

    inline bool operator<(const Message& other) const { return _msgId < other._msgId; }

private:
    QDateTime _timestamp;
    MsgId _msgId;
    BufferInfo _bufferInfo;
    QString _contents;
    QString _sender;
    QString _senderPrefixes;
    QString _realName;
    QString _avatarUrl;
    Type _type;
    Flags _flags;

    friend QDataStream& operator>>(QDataStream& in, Message& msg);
};

using MessageList = QList<Message>;

QDataStream& operator<<(QDataStream& out, const Message& msg);
QDataStream& operator>>(QDataStream& in, Message& msg);
QDebug operator<<(QDebug dbg, const Message& msg);

Q_DECLARE_METATYPE(Message)
Q_DECLARE_OPERATORS_FOR_FLAGS(Message::Types)
Q_DECLARE_OPERATORS_FOR_FLAGS(Message::Flags)
