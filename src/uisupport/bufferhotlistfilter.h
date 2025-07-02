// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

#include "uisupport-export.h"

#include <QSortFilterProxyModel>

#include "types.h"

class UISUPPORT_EXPORT BufferHotListFilter : public QSortFilterProxyModel
{
    Q_OBJECT

public:
    BufferHotListFilter(QAbstractItemModel* source, QObject* parent = nullptr);

    inline int columnCount(const QModelIndex&) const override { return 1; }
    BufferId hottestBuffer();
    //   QVariant data(const QModelIndex &index, int role) const;

protected:
    bool filterAcceptsRow(int source_row, const QModelIndex& source_parent) const override;
    bool lessThan(const QModelIndex& source_left, const QModelIndex& source_right) const override;
};
