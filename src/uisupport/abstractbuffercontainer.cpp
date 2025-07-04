// SPDX-FileCopyrightText: 2005-2025 Quassel Project <devel@quassel-irc.org>
// SPDX-License-Identifier: GPL-2.0-or-later

#include "abstractbuffercontainer.h"

#include "client.h"
#include "clientbacklogmanager.h"
#include "networkmodel.h"

AbstractBufferContainer::AbstractBufferContainer(QWidget* parent)
    : AbstractItemView(parent)
    , _currentBuffer(0)
{
}

void AbstractBufferContainer::rowsAboutToBeRemoved(const QModelIndex& parent, int start, int end)
{
    Q_ASSERT(model());
    if (!parent.isValid()) {
        // ok this means that whole networks are about to be removed
        // we can't determine which buffers are affect, so we hope that all nets are removed
        // this is the most common case (for example disconnecting from the core or terminating the client)
        if (model()->rowCount(parent) != end - start + 1)
            return;

        foreach (BufferId id, _chatViews.keys()) {
            removeChatView(id);
        }
        _chatViews.clear();
    }
    else {
        // check if there are explicitly buffers removed
        // Make sure model is valid first
        if (!parent.model()) {
            return;
        }
        for (int i = start; i <= end; i++) {
            QVariant variant = parent.model()->index(i, 0, parent).data(NetworkModel::BufferIdRole);
            if (!variant.isValid())
                continue;

            BufferId bufferId = variant.value<BufferId>();
            removeBuffer(bufferId);
        }
    }
}

void AbstractBufferContainer::removeBuffer(BufferId bufferId)
{
    if (!_chatViews.contains(bufferId))
        return;

    removeChatView(bufferId);
    _chatViews.take(bufferId);
}

/*
  Switching to first buffer is now handled in MainWin::clientNetworkUpdated()

void AbstractBufferContainer::rowsInserted(const QModelIndex &parent, int start, int end) {
  Q_UNUSED(end)

  if(currentBuffer().isValid())
    return;

  // we want to make sure the very first valid buffer is selected
  QModelIndex index = model()->index(start, 0, parent);
  if(index.isValid()) {
    BufferId id = index.data(NetworkModel::BufferIdRole).value<BufferId>();
    if(id.isValid())
      setCurrentBuffer(id);
  }
}
*/

void AbstractBufferContainer::currentChanged(const QModelIndex& current, const QModelIndex& previous)
{
    Q_UNUSED(previous)

    BufferId newBufferId = current.data(NetworkModel::BufferIdRole).value<BufferId>();
    // To be able to reset the selected buffer, we don't check if buffer/index is valid here
    if (currentBuffer() != newBufferId) {
        setCurrentBuffer(newBufferId);
        emit currentChanged(newBufferId);
        emit currentChanged(current);
    }
}

void AbstractBufferContainer::setCurrentBuffer(BufferId bufferId)
{
    BufferId prevBufferId = currentBuffer();
    if (prevBufferId.isValid() && _chatViews.contains(prevBufferId)) {
        MsgId msgId = _chatViews.value(prevBufferId)->lastMsgId();
        Client::setBufferLastSeenMsg(prevBufferId, msgId);
    }

    if (!bufferId.isValid()) {
        _currentBuffer = 0;
        showChatView(0);
        return;
    }

    if (!_chatViews.contains(bufferId))
        _chatViews[bufferId] = createChatView(bufferId);

    _currentBuffer = bufferId;
    showChatView(bufferId);
    Client::networkModel()->clearBufferActivity(bufferId);
    Client::setBufferLastSeenMsg(bufferId, _chatViews[bufferId]->lastMsgId());
    Client::backlogManager()->checkForBacklog(bufferId);
    setFocus();
}
