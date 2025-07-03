// SPDX-FileCopyrightText: 2005-2025 Quassel Project <devel@quassel-irc.org>
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

#include "buffersyncer.h"

class CoreSession;

class CoreBufferSyncer : public BufferSyncer
{
    Q_OBJECT

public:
    explicit CoreBufferSyncer(CoreSession* parent);

public slots:
    void requestSetLastSeenMsg(BufferId buffer, const MsgId& msgId) override;
    void requestSetMarkerLine(BufferId buffer, const MsgId& msgId) override;

    inline void requestRemoveBuffer(BufferId buffer) override { removeBuffer(buffer); }
    void removeBuffer(BufferId bufferId) override;

    void addBufferActivity(const Message& message)
    {
        if (message.flags().testFlag(Message::Flag::Ignored)) {
            // Don't update buffer activity with messages that are ignored
            return;
        }
        auto oldActivity = activity(message.bufferId());
        if (!oldActivity.testFlag(message.type())) {
            setBufferActivity(message.bufferId(), (int)(oldActivity | message.type()));
        }
    }

    void addCoreHighlight(const Message& message)
    {
        if (message.flags().testFlag(Message::Flag::Ignored)) {
            // Don't increase highlight count for messages that are ignored
            return;
        }
        auto oldHighlightCount = highlightCount(message.bufferId());
        if (message.flags().testFlag(Message::Flag::Highlight) && !message.flags().testFlag(Message::Flag::Self)) {
            setHighlightCount(message.bufferId(), oldHighlightCount + 1);
        }
    }

    void setBufferActivity(BufferId buffer, int activity) override;

    void setHighlightCount(BufferId buffer, int highlightCount) override;

    inline void requestRenameBuffer(BufferId buffer, QString newName) override { renameBuffer(buffer, newName); }
    void renameBuffer(BufferId buffer, QString newName) override;

    inline void requestMergeBuffersPermanently(BufferId buffer1, BufferId buffer2) override { mergeBuffersPermanently(buffer1, buffer2); }
    void mergeBuffersPermanently(BufferId buffer1, BufferId buffer2) override;

    void requestPurgeBufferIds() override;

    inline void requestMarkBufferAsRead(BufferId buffer) override
    {
        int activity = Message::Types();
        setBufferActivity(buffer, activity);
        setHighlightCount(buffer, 0);
        markBufferAsRead(buffer);
    }

    void storeDirtyIds();

protected:
    void customEvent(QEvent* event) override;

private:
    CoreSession* _coreSession;
    bool _purgeBuffers;

    QSet<BufferId> dirtyLastSeenBuffers;
    QSet<BufferId> dirtyMarkerLineBuffers;
    QSet<BufferId> dirtyActivities;
    QSet<BufferId> dirtyHighlights;

    void purgeBufferIds();
};
