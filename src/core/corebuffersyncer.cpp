// SPDX-FileCopyrightText: 2005-2025 Quassel Project <devel@quassel-irc.org>
// SPDX-License-Identifier: GPL-2.0-or-later

#include "corebuffersyncer.h"

#include <algorithm>
#include <iterator>
#include <set>

#include "core.h"
#include "corenetwork.h"
#include "coresession.h"
#include "ircchannel.h"
#include "util.h"

class PurgeEvent : public QEvent
{
public:
    PurgeEvent()
        : QEvent(QEvent::User)
    {
    }
};

CoreBufferSyncer::CoreBufferSyncer(CoreSession* parent)
    : BufferSyncer(Core::bufferLastMsgIds(parent->user()),
                   Core::bufferLastSeenMsgIds(parent->user()),
                   Core::bufferMarkerLineMsgIds(parent->user()),
                   Core::bufferActivities(parent->user()),
                   Core::highlightCounts(parent->user()),
                   parent)
    , _coreSession(parent)
    , _purgeBuffers(false)
{
    connect(parent, &CoreSession::displayMsg, this, &CoreBufferSyncer::addBufferActivity);
    connect(parent, &CoreSession::displayMsg, this, &CoreBufferSyncer::addCoreHighlight);
}

void CoreBufferSyncer::requestSetLastSeenMsg(BufferId buffer, const MsgId& msgId)
{
    if (setLastSeenMsg(buffer, msgId)) {
        int activity = Core::bufferActivity(buffer, msgId);
        int highlightCount = Core::highlightCount(buffer, msgId);

        setBufferActivity(buffer, activity);
        setHighlightCount(buffer, highlightCount);

        dirtyLastSeenBuffers << buffer;
    }
}

void CoreBufferSyncer::requestSetMarkerLine(BufferId buffer, const MsgId& msgId)
{
    if (setMarkerLine(buffer, msgId))
        dirtyMarkerLineBuffers << buffer;
}

void CoreBufferSyncer::storeDirtyIds()
{
    UserId userId = _coreSession->user();
    MsgId msgId;
    foreach (BufferId bufferId, dirtyLastSeenBuffers) {
        msgId = lastSeenMsg(bufferId);
        if (msgId.isValid())
            Core::setBufferLastSeenMsg(userId, bufferId, msgId);
    }

    foreach (BufferId bufferId, dirtyMarkerLineBuffers) {
        msgId = markerLine(bufferId);
        if (msgId.isValid())
            Core::setBufferMarkerLineMsg(userId, bufferId, msgId);
    }

    foreach (BufferId bufferId, dirtyActivities) {
        Core::setBufferActivity(userId, bufferId, activity(bufferId));
    }

    foreach (BufferId bufferId, dirtyHighlights) {
        Core::setHighlightCount(userId, bufferId, highlightCount(bufferId));
    }

    dirtyLastSeenBuffers.clear();
    dirtyMarkerLineBuffers.clear();
    dirtyActivities.clear();
    dirtyHighlights.clear();
}

void CoreBufferSyncer::removeBuffer(BufferId bufferId)
{
    BufferInfo bufferInfo = Core::getBufferInfo(_coreSession->user(), bufferId);
    if (!bufferInfo.isValid()) {
        qWarning() << "CoreBufferSyncer::removeBuffer(): invalid BufferId:" << bufferId << "for User:" << _coreSession->user();
        return;
    }

    if (bufferInfo.type() == BufferInfo::StatusBuffer) {
        qWarning() << "CoreBufferSyncer::removeBuffer(): Status Buffers cannot be removed!";
        return;
    }

    if (bufferInfo.type() == BufferInfo::ChannelBuffer) {
        CoreNetwork* net = _coreSession->network(bufferInfo.networkId());
        if (!net) {
            qWarning() << "CoreBufferSyncer::removeBuffer(): Received BufferInfo with unknown networkId!";
            return;
        }
        IrcChannel* chan = net->ircChannel(bufferInfo.bufferName());
        if (chan) {
            qWarning() << "CoreBufferSyncer::removeBuffer(): Unable to remove Buffer for joined Channel:" << bufferInfo.bufferName();
            return;
        }
    }
    if (Core::removeBuffer(_coreSession->user(), bufferId))
        BufferSyncer::removeBuffer(bufferId);
}

void CoreBufferSyncer::renameBuffer(BufferId bufferId, QString newName)
{
    BufferInfo bufferInfo = Core::getBufferInfo(_coreSession->user(), bufferId);
    if (!bufferInfo.isValid()) {
        qWarning() << "CoreBufferSyncer::renameBuffer(): invalid BufferId:" << bufferId << "for User:" << _coreSession->user();
        return;
    }

    if (bufferInfo.type() != BufferInfo::QueryBuffer) {
        qWarning() << "CoreBufferSyncer::renameBuffer(): only QueryBuffers can be renamed" << bufferId;
        return;
    }

    if (Core::renameBuffer(_coreSession->user(), bufferId, newName))
        BufferSyncer::renameBuffer(bufferId, newName);
}

void CoreBufferSyncer::mergeBuffersPermanently(BufferId bufferId1, BufferId bufferId2)
{
    BufferInfo bufferInfo1 = Core::getBufferInfo(_coreSession->user(), bufferId1);
    BufferInfo bufferInfo2 = Core::getBufferInfo(_coreSession->user(), bufferId2);
    if (!bufferInfo1.isValid() || !bufferInfo2.isValid()) {
        qWarning() << "CoreBufferSyncer::mergeBuffersPermanently(): invalid BufferIds:" << bufferId1 << bufferId2
                   << "for User:" << _coreSession->user();
        return;
    }

    if ((bufferInfo1.type() != BufferInfo::QueryBuffer && bufferInfo1.type() != BufferInfo::ChannelBuffer)
        || (bufferInfo2.type() != BufferInfo::QueryBuffer && bufferInfo2.type() != BufferInfo::ChannelBuffer)) {
        qWarning() << "CoreBufferSyncer::mergeBuffersPermanently(): only QueryBuffers and/or ChannelBuffers can be merged!" << bufferId1
                   << bufferId2;
        return;
    }

    if (Core::mergeBuffersPermanently(_coreSession->user(), bufferId1, bufferId2)) {
        BufferSyncer::mergeBuffersPermanently(bufferId1, bufferId2);
    }
}

void CoreBufferSyncer::customEvent(QEvent* event)
{
    if (event->type() != QEvent::User)
        return;

    purgeBufferIds();
    event->accept();
}

void CoreBufferSyncer::requestPurgeBufferIds()
{
    if (_purgeBuffers)
        return;

    _purgeBuffers = true;
    QCoreApplication::postEvent(this, new PurgeEvent());
}

void CoreBufferSyncer::purgeBufferIds()
{
    _purgeBuffers = false;
    auto bufferInfos = Core::requestBuffers(_coreSession->user());
    std::set<BufferId> actualBuffers;
    std::transform(bufferInfos.cbegin(), bufferInfos.cend(), std::inserter(actualBuffers, actualBuffers.end()), [](auto&& bufferInfo) {
        return bufferInfo.bufferId();
    });

    QSet<BufferId> storedIds = toQSet(lastSeenBufferIds()) + toQSet(markerLineBufferIds());
    foreach (BufferId bufferId, storedIds) {
        if (actualBuffers.find(bufferId) == actualBuffers.end()) {
            BufferSyncer::removeBuffer(bufferId);
        }
    }
}

void CoreBufferSyncer::setBufferActivity(BufferId buffer, int activity)
{
    BufferSyncer::setBufferActivity(buffer, activity);
    dirtyActivities << buffer;
}

void CoreBufferSyncer::setHighlightCount(BufferId buffer, int highlightCount)
{
    BufferSyncer::setHighlightCount(buffer, highlightCount);
    dirtyHighlights << buffer;
}
