// SPDX-FileCopyrightText: 2005-2025 Quassel Project <devel@quassel-irc.org>
// SPDX-License-Identifier: GPL-2.0-or-later

#include "nickviewfilter.h"

#include "buffersettings.h"
#include "graphicalui.h"
#include "networkmodel.h"
#include "uistyle.h"

/******************************************************************************************
 * NickViewFilter
 ******************************************************************************************/
NickViewFilter::NickViewFilter(const BufferId& bufferId, NetworkModel* parent)
    : QSortFilterProxyModel(parent)
    , _bufferId(bufferId)
{
    setSourceModel(parent);
    setDynamicSortFilter(true);
    setSortCaseSensitivity(Qt::CaseInsensitive);
    setSortRole(TreeModel::SortRole);
}

bool NickViewFilter::filterAcceptsRow(int source_row, const QModelIndex& source_parent) const
{
    // root node, networkindexes, the bufferindex of the buffer this filter is active for and it's children are accepted
    if (!(source_parent.isValid() && source_parent.model()))
        return true;

    QModelIndex source_child = source_parent.model()->index(source_row, 0, source_parent);
    return (sourceModel()->data(source_child, NetworkModel::BufferIdRole).value<BufferId>() == _bufferId);
}

QVariant NickViewFilter::data(const QModelIndex& index, int role) const
{
    switch (role) {
    case Qt::FontRole:
    case Qt::ForegroundRole:
    case Qt::BackgroundRole:
    case Qt::DecorationRole:
        return GraphicalUi::uiStyle()->nickViewItemData(mapToSource(index), role);
    default:
        return QSortFilterProxyModel::data(index, role);
    }
}
