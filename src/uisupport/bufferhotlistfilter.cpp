// SPDX-License-Identifier: GPL-2.0-or-later

#include "bufferhotlistfilter.h"

#include "networkmodel.h"

BufferHotListFilter::BufferHotListFilter(QAbstractItemModel* source, QObject* parent)
    : QSortFilterProxyModel(parent)
{
    setSourceModel(source);
    setDynamicSortFilter(true);
    sort(0, Qt::DescendingOrder);  // enable sorting... this is "usually" triggered by a enabling setSortingEnabled(true) on a view;
}

BufferId BufferHotListFilter::hottestBuffer()
{
    invalidate();
    sort(0, Qt::DescendingOrder);
    QModelIndex topIndex = index(0, 0);
    return data(topIndex, NetworkModel::BufferIdRole).value<BufferId>();
}

bool BufferHotListFilter::filterAcceptsRow(int source_row, const QModelIndex& source_parent) const
{
    Q_ASSERT(sourceModel());
    QModelIndex source_index = sourceModel()->index(source_row, 0, source_parent);

    MsgId firstUnreadMsgId = sourceModel()->data(source_index, NetworkModel::BufferFirstUnreadMsgIdRole).value<MsgId>();
    if (!firstUnreadMsgId.isValid())
        return false;

    // filter out statusbuffers (it's accessible as networkitem)
    BufferInfo::Type bufferType = (BufferInfo::Type)sourceModel()->data(source_index, NetworkModel::BufferTypeRole).toInt();
    if (bufferType == BufferInfo::StatusBuffer) {
        NetworkModel::ItemType itemType = (NetworkModel::ItemType)sourceModel()->data(source_index, NetworkModel::ItemTypeRole).toInt();
        return itemType == NetworkModel::NetworkItemType;
    }

    return true;
}

bool BufferHotListFilter::lessThan(const QModelIndex& source_left, const QModelIndex& source_right) const
{
    int leftActivity = sourceModel()->data(source_left, NetworkModel::BufferActivityRole).toInt();
    int rightActivity = sourceModel()->data(source_right, NetworkModel::BufferActivityRole).toInt();
    if (leftActivity != rightActivity)
        return leftActivity < rightActivity;

    MsgId leftUnreadMsgId = sourceModel()->data(source_left, NetworkModel::BufferFirstUnreadMsgIdRole).value<MsgId>();
    MsgId rightUnreadMsgId = sourceModel()->data(source_right, NetworkModel::BufferFirstUnreadMsgIdRole).value<MsgId>();
    return leftUnreadMsgId > rightUnreadMsgId;  // newer messages are treated to be "less"
}

// QVariant BufferHotListFilter::data(const QModelIndex &index, int role) const {
//   QVariant d = QSortFilterProxyModel::data(index, role);

//   if(role == Qt::DisplayRole) {
//     int activity = QSortFilterProxyModel::data(index, NetworkModel::BufferActivityRole).toInt();
//     MsgId unreadMsgId = QSortFilterProxyModel::data(index, NetworkModel::BufferFirstUnreadMsgIdRole).value<MsgId>();
//     return QString("%1 %2 %3").arg(d.toString()).arg(activity).arg(unreadMsgId.toInt());
//   }
//   return d;
// }
