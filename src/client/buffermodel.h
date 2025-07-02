// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

#include "client-export.h"

#include <QItemSelectionModel>
#include <QPair>
#include <QSortFilterProxyModel>

#include "network.h"
#include "networkmodel.h"
#include "selectionmodelsynchronizer.h"
#include "types.h"

class QAbstractItemView;

class CLIENT_EXPORT BufferModel : public QSortFilterProxyModel
{
    Q_OBJECT

public:
    BufferModel(NetworkModel* parent = nullptr);

    bool filterAcceptsRow(int sourceRow, const QModelIndex& parent) const override;

    inline const SelectionModelSynchronizer* selectionModelSynchronizer() const { return &_selectionModelSynchronizer; }
    inline QItemSelectionModel* standardSelectionModel() const { return _selectionModelSynchronizer.selectionModel(); }

    inline void synchronizeSelectionModel(QItemSelectionModel* selectionModel)
    {
        _selectionModelSynchronizer.synchronizeSelectionModel(selectionModel);
    }
    void synchronizeView(QAbstractItemView* view);

    inline QModelIndex currentIndex() { return standardSelectionModel()->currentIndex(); }
    inline BufferId currentBuffer() { return currentIndex().data(NetworkModel::BufferIdRole).value<BufferId>(); }

public slots:
    void setCurrentIndex(const QModelIndex& newCurrent);
    void switchToBuffer(const BufferId& bufferId);
    void switchToBufferIndex(const QModelIndex& bufferIdx);
    void switchToOrJoinBuffer(NetworkId network, const QString& bufferName, bool isQuery = false);
    void switchToOrStartQuery(NetworkId network, const QString& nick) { switchToOrJoinBuffer(network, nick, true); }

    void switchToBufferAfterCreation(NetworkId network, const QString& name);

private slots:
    void debug_currentChanged(QModelIndex current, QModelIndex previous);
    void newNetwork(NetworkId id);
    void networkConnectionChanged(Network::ConnectionState state);
    void newBuffers(const QModelIndex& parent, int start, int end);

private:
    void newBuffer(BufferId bufferId);

    SelectionModelSynchronizer _selectionModelSynchronizer;
    QPair<NetworkId, QString> _bufferToSwitchTo;
};
