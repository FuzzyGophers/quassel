// SPDX-FileCopyrightText: 2005-2025 Quassel Project <devel@quassel-irc.org>
// SPDX-License-Identifier: GPL-2.0-or-later

#include "debugmessagemodelfilter.h"

#include "messagemodel.h"

DebugMessageModelFilter::DebugMessageModelFilter(QObject* parent)
    : QSortFilterProxyModel(parent)
{}

QVariant DebugMessageModelFilter::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (orientation != Qt::Horizontal || role != Qt::DisplayRole)
        return QVariant();

    switch (section) {
    case 0:
        return "MessageId";
    case 1:
        return "Sender";
    case 2:
        return "Message";
    default:
        return QVariant();
    }
}

QVariant DebugMessageModelFilter::data(const QModelIndex& index, int role) const
{
    if (index.column() != 0 || role != Qt::DisplayRole)
        return QSortFilterProxyModel::data(index, role);

    if (!sourceModel())
        return QVariant();

    QModelIndex source_index = mapToSource(index);
    return sourceModel()->data(source_index, MessageModel::MsgIdRole).value<MsgId>().toQint64();
}
