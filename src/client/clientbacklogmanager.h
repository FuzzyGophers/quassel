// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

#include "client-export.h"

#include "backlogmanager.h"
#include "message.h"

class BacklogRequester;

class CLIENT_EXPORT ClientBacklogManager : public BacklogManager
{
    Q_OBJECT

public:
    ClientBacklogManager(QObject* parent = nullptr);

    // helper for the backlogRequester, as it isn't a QObject and can't emit itself
    inline void emitMessagesRequested(const QString& msg) const { emit messagesRequested(msg); }

    void reset();

public slots:
    QVariantList requestBacklog(BufferId bufferId, MsgId first = -1, MsgId last = -1, int limit = -1, int additional = 0) override;
    void receiveBacklog(BufferId bufferId, MsgId first, MsgId last, int limit, int additional, QVariantList msgs) override;
    void receiveBacklogAll(MsgId first, MsgId last, int limit, int additional, QVariantList msgs) override;

    void requestInitialBacklog();

    void checkForBacklog(BufferId bufferId);
    void checkForBacklog(const BufferIdList& bufferIds);

signals:
    void messagesReceived(BufferId bufferId, int count) const;
    void messagesRequested(const QString&) const;
    void messagesProcessed(const QString&) const;

    void updateProgress(int, int);

private:
    bool isBuffering();
    BufferIdList filterNewBufferIds(const BufferIdList& bufferIds);

    void dispatchMessages(const MessageList& messages, bool sort = false);

    BacklogRequester* _requester{nullptr};
    bool _initBacklogRequested{false};
    QSet<BufferId> _buffersRequested;
};

// inlines
inline void ClientBacklogManager::checkForBacklog(BufferId bufferId)
{
    checkForBacklog(BufferIdList() << bufferId);
}
