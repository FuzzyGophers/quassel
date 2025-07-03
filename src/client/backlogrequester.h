// SPDX-FileCopyrightText: 2005-2025 Quassel Project <devel@quassel-irc.org>
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

#include <set>

#include <QList>

#include "client.h"
#include "message.h"
#include "networkmodel.h"
#include "types.h"

class ClientBacklogManager;

class BacklogRequester
{
public:
    enum RequesterType
    {
        InvalidRequester = 0,
        PerBufferFixed,
        PerBufferUnread,
        AsNeeded,              ///< Only request backlog on cores without Feature::BufferActivitySync
        GlobalUnread
    };

    BacklogRequester(bool buffering, RequesterType requesterType, ClientBacklogManager* backlogManger);
    virtual ~BacklogRequester() = default;

    inline bool isBuffering() { return _isBuffering; }
    inline RequesterType type() { return _requesterType; }
    inline const QList<Message>& bufferedMessages() { return _bufferedMessages; }

    inline int buffersWaiting() const { return int(_buffersWaiting.size()); }
    inline int totalBuffers() const { return _totalBuffers; }

    bool buffer(BufferId bufferId, const MessageList& messages);  //! returns false if it was the last missing backlogpart

    virtual void requestBacklog(const BufferIdList& bufferIds) = 0;
    virtual inline void requestInitialBacklog() { requestBacklog(allBufferIds()); }

    virtual void flushBuffer();

protected:
    BufferIdList allBufferIds() const;
    void setWaitingBuffers(const BufferIdList& buffers);

    ClientBacklogManager* backlogManager;

private:
    bool _isBuffering;
    RequesterType _requesterType;
    MessageList _bufferedMessages;
    int _totalBuffers;
    std::set<BufferId> _buffersWaiting;
};

// ========================================
//  FIXED BACKLOG REQUESTER
// ========================================
class FixedBacklogRequester : public BacklogRequester
{
public:
    FixedBacklogRequester(ClientBacklogManager* backlogManager);
    void requestBacklog(const BufferIdList& bufferIds) override;

private:
    int _backlogCount;
};

// ========================================
//  GLOBAL UNREAD BACKLOG REQUESTER
// ========================================
class GlobalUnreadBacklogRequester : public BacklogRequester
{
public:
    GlobalUnreadBacklogRequester(ClientBacklogManager* backlogManager);
    void requestInitialBacklog() override;
    void requestBacklog(const BufferIdList&) override {}

private:
    int _limit;
    int _additional;
};

// ========================================
//  PER BUFFER UNREAD BACKLOG REQUESTER
// ========================================
class PerBufferUnreadBacklogRequester : public BacklogRequester
{
public:
    PerBufferUnreadBacklogRequester(ClientBacklogManager* backlogManager);
    void requestBacklog(const BufferIdList& bufferIds) override;

private:
    int _limit;
    int _additional;
};

// ========================================
//  AS NEEDED BACKLOG REQUESTER
// ========================================
/**
 * Backlog requester that only fetches initial backlog when the core doesn't support buffer activity
 * tracking
 */
class AsNeededBacklogRequester : public BacklogRequester
{
public:
    AsNeededBacklogRequester(ClientBacklogManager* backlogManager);
    void requestBacklog(const BufferIdList& bufferIds) override;

private:
    int _legacyBacklogCount;
};
