// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

#include "uisupport-export.h"

#include <QSortFilterProxyModel>

#include "types.h"

class NetworkModel;

// This is proxymodel is purely for the sorting right now
class UISUPPORT_EXPORT NickViewFilter : public QSortFilterProxyModel
{
    Q_OBJECT

public:
    NickViewFilter(const BufferId& bufferId, NetworkModel* parent = nullptr);

    QVariant data(const QModelIndex& index, int role) const override;
    QVariant icon(const QModelIndex& index) const;

protected:
    bool filterAcceptsRow(int source_row, const QModelIndex& source_parent) const override;
    QVariant styleData(const QModelIndex& index, int role) const;

private:
    BufferId _bufferId;
};
