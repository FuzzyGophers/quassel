// SPDX-FileCopyrightText: 2005-2025 Quassel Project <devel@quassel-irc.org>
// SPDX-License-Identifier: GPL-2.0-or-later

#include "awaylogfilter.h"

#include "clientignorelistmanager.h"

AwayLogFilter::AwayLogFilter(MessageModel* model, QObject* parent)
    : ChatMonitorFilter(model, parent)
{}

bool AwayLogFilter::filterAcceptsRow(int sourceRow, const QModelIndex& sourceParent) const
{
    Q_UNUSED(sourceParent)

    QModelIndex source_index = sourceModel()->index(sourceRow, 0);

    Message::Flags flags = (Message::Flags)sourceModel()->data(source_index, MessageModel::FlagsRole).toInt();
    // Only show highlights from the backlog
    if (!(flags & Message::Backlog && flags & Message::Highlight)) {
        return false;
    }

    // do not use invalid buffers
    BufferId bufferId = sourceModel()->data(source_index, MessageModel::BufferIdRole).value<BufferId>();
    if (!bufferId.isValid()) {
        return false;
    }

    // only show messages that were sent after the user detached
    if (Client::networkModel()->lastSeenMsgId(bufferId) >= sourceModel()->data(source_index, MessageModel::MsgIdRole).value<MsgId>()) {
        return false;
    }

    // ignorelist handling
    // only match if message is not flagged as server msg
    if (!(flags & Message::ServerMsg) && Client::ignoreListManager()
        && Client::ignoreListManager()->match(source_index.data(MessageModel::MessageRole).value<Message>(),
                                              Client::networkModel()->networkName(bufferId))) {
        return false;
    }

    return true;
}

QVariant AwayLogFilter::data(const QModelIndex& index, int role) const
{
    if (role != MessageModel::FlagsRole)
        return ChatMonitorFilter::data(index, role);

    QModelIndex source_index = mapToSource(index);
    Message::Flags flags = (Message::Flags)sourceModel()->data(source_index, MessageModel::FlagsRole).toInt();
    flags &= ~Message::Highlight;
    return (int)flags;
}
