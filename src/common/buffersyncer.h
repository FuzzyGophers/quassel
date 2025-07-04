// SPDX-FileCopyrightText: 2005-2025 Quassel Project <devel@quassel-irc.org>
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

#include "common-export.h"

#include "message.h"
#include "syncableobject.h"
#include "types.h"

class COMMON_EXPORT BufferSyncer : public SyncableObject
{
    Q_OBJECT
    SYNCABLE_OBJECT

public:
    explicit BufferSyncer(QObject* parent);
    explicit BufferSyncer(QHash<BufferId, MsgId> lastMsg,
                          QHash<BufferId, MsgId> lastSeenMsg,
                          QHash<BufferId, MsgId> markerLines,
                          QHash<BufferId, Message::Types> activities,
                          QHash<BufferId, int> highlightCounts,
                          QObject* parent);

    MsgId lastSeenMsg(BufferId buffer) const;
    MsgId lastMsg(BufferId buffer) const;
    MsgId markerLine(BufferId buffer) const;
    Message::Types activity(BufferId buffer) const;
    int highlightCount(BufferId buffer) const;

    void markActivitiesChanged()
    {
        for (auto buffer : _bufferActivities.keys()) {
            emit bufferActivityChanged(buffer, activity(buffer));
        }
    }

    void markHighlightCountsChanged()
    {
        for (auto buffer : _highlightCounts.keys()) {
            emit highlightCountChanged(buffer, highlightCount(buffer));
        }
    }

public slots:
    QVariantList initLastMsg() const;
    void initSetLastMsg(const QVariantList&);

    QVariantList initLastSeenMsg() const;
    void initSetLastSeenMsg(const QVariantList&);

    QVariantList initMarkerLines() const;
    void initSetMarkerLines(const QVariantList&);

    QVariantList initActivities() const;
    void initSetActivities(const QVariantList&);

    QVariantList initHighlightCounts() const;
    void initSetHighlightCounts(const QVariantList&);

    virtual inline void setLastMsg(BufferId buffer, const MsgId& msgId)
    {
        SYNC(ARG(buffer), ARG(msgId));
        _lastMsg[buffer] = msgId;
        emit lastMsgSet(buffer, msgId);
    }

    virtual inline void requestSetLastSeenMsg(BufferId buffer, const MsgId& msgId) { REQUEST(ARG(buffer), ARG(msgId)) }
    virtual inline void requestSetMarkerLine(BufferId buffer, const MsgId& msgId)
    {
        REQUEST(ARG(buffer), ARG(msgId)) setMarkerLine(buffer, msgId);
    }

    virtual inline void setBufferActivity(BufferId buffer, int activity)
    {
        auto flags = Message::Types(activity);
        SYNC(ARG(buffer), ARG(activity));
        _bufferActivities[buffer] = flags;
        emit bufferActivityChanged(buffer, flags);
    }

    virtual inline void setHighlightCount(BufferId buffer, int count)
    {
        SYNC(ARG(buffer), ARG(count));
        _highlightCounts[buffer] = count;
        emit highlightCountChanged(buffer, count);
    }

    virtual inline void requestRemoveBuffer(BufferId buffer) { REQUEST(ARG(buffer)) }
    virtual void removeBuffer(BufferId buffer);

    virtual inline void requestRenameBuffer(BufferId buffer, QString newName) { REQUEST(ARG(buffer), ARG(newName)) }
    virtual inline void renameBuffer(BufferId buffer, QString newName)
    {
        SYNC(ARG(buffer), ARG(newName)) emit bufferRenamed(buffer, newName);
    }

    virtual inline void requestMergeBuffersPermanently(BufferId buffer1, BufferId buffer2) { emit REQUEST(ARG(buffer1), ARG(buffer2)) }
    virtual void mergeBuffersPermanently(BufferId buffer1, BufferId buffer2);

    virtual inline void requestPurgeBufferIds() { REQUEST(NO_ARG); }

    virtual inline void requestMarkBufferAsRead(BufferId buffer) { REQUEST(ARG(buffer)) emit bufferMarkedAsRead(buffer); }
    virtual inline void markBufferAsRead(BufferId buffer) { SYNC(ARG(buffer)) emit bufferMarkedAsRead(buffer); }

signals:
    void lastMsgSet(BufferId buffer, const MsgId& msgId);
    void lastSeenMsgSet(BufferId buffer, const MsgId& msgId);
    void markerLineSet(BufferId buffer, const MsgId& msgId);
    void bufferRemoved(BufferId buffer);
    void bufferRenamed(BufferId buffer, QString newName);
    void buffersPermanentlyMerged(BufferId buffer1, BufferId buffer2);
    void bufferMarkedAsRead(BufferId buffer);
    void bufferActivityChanged(BufferId, Message::Types);
    void highlightCountChanged(BufferId, int);

protected slots:
    bool setLastSeenMsg(BufferId buffer, const MsgId& msgId);
    bool setMarkerLine(BufferId buffer, const MsgId& msgId);

protected:
    inline QList<BufferId> lastBufferIds() const { return _lastMsg.keys(); }
    inline QList<BufferId> lastSeenBufferIds() const { return _lastSeenMsg.keys(); }
    inline QList<BufferId> markerLineBufferIds() const { return _markerLines.keys(); }
    inline QHash<BufferId, MsgId> markerLines() const { return _markerLines; }

private:
    QHash<BufferId, MsgId> _lastMsg;
    QHash<BufferId, MsgId> _lastSeenMsg;
    QHash<BufferId, MsgId> _markerLines;
    QHash<BufferId, Message::Types> _bufferActivities;
    QHash<BufferId, int> _highlightCounts;
};
