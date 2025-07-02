// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

#include "common-export.h"

#include "message.h"
#include "networkevent.h"

// this corresponds to CoreSession::RawMessage for now and should contain the information we need to convert events
// into messages for the legacy code to work with

class COMMON_EXPORT MessageEvent : public NetworkEvent
{
public:
    explicit MessageEvent(Message::Type msgType,
                          Network* network,
                          QString msg,
                          QString sender = {},
                          QString target = {},
                          Message::Flags msgFlags = Message::None,
                          const QDateTime& timestamp = {});

    inline Message::Type msgType() const { return _msgType; }
    inline void setMsgType(Message::Type type) { _msgType = type; }

    inline BufferInfo::Type bufferType() const { return _bufferType; }
    inline void setBufferType(BufferInfo::Type type) { _bufferType = type; }

    inline QString target() const { return _target; }
    inline QString text() const { return _text; }
    inline QString sender() const { return _sender; }

    inline Message::Flags msgFlags() const { return _msgFlags; }
    inline void setMsgFlag(Message::Flag flag) { _msgFlags |= flag; }
    inline void setMsgFlags(Message::Flags flags) { _msgFlags = flags; }

    static Event* create(EventManager::EventType type, QVariantMap& map, Network* network);

protected:
    explicit MessageEvent(EventManager::EventType type, QVariantMap& map, Network* network);
    void toVariantMap(QVariantMap& map) const override;

    inline QString className() const override { return "MessageEvent"; }
    inline void debugInfo(QDebug& dbg) const override
    {
        NetworkEvent::debugInfo(dbg);
        dbg.nospace() << ", sender = " << qPrintable(sender())
                      << ", target = " << qPrintable(target())
                      << ", text = " << text()
                      << ", msgtype = " << qPrintable(QString::number(msgType(), 16))
                      << ", buffertype = " << qPrintable(QString::number(bufferType(), 16))
                      << ", msgflags = " << qPrintable(QString::number(msgFlags(), 16));
    }

private:
    BufferInfo::Type bufferTypeByTarget(const QString& target) const;

    Message::Type _msgType;
    BufferInfo::Type _bufferType;
    QString _text, _sender, _target;
    Message::Flags _msgFlags;
};
