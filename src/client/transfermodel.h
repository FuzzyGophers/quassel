// SPDX-FileCopyrightText: 2005-2025 Quassel Project <devel@quassel-irc.org>
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

#include <QAbstractTableModel>
#include <QString>
#include <QUuid>
#include <QVector>

#include "transfer.h"

class TransferManager;

/**
 * Model that holds the current list of transfers.
 */
class TransferModel : public QAbstractTableModel
{
    Q_OBJECT

public:
    using QAbstractTableModel::QAbstractTableModel;

    // see base class docs
    int rowCount(const QModelIndex& index = {}) const override;
    int columnCount(const QModelIndex& index = {}) const override;
    QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const override;
    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;

    /**
     * Access the transfer for the given ID
     *
     * @param[in] transferId Transfer ID
     * @returns A pointer to the transfer with the given ID, or nullptr for an unknown ID
     */
    Transfer* transfer(const QUuid& transferId) const;

    /**
     * Sets the TransferManager associated with this model.
     *
     * The model receives data from the given TransferManager instance. If set to nullptr, the model
     * is cleared.
     *
     * @param[in] manager Pointer to the TransferManager instance, or nullptr for clearing the model
     */
    void setManager(const TransferManager* manager);

private slots:
    /**
     * Slot to be called when a transfer is added.
     *
     * @param[in] transferId The transfer's ID
     */
    void onTransferAdded(const QUuid& transferId);

    /**
     * Slot to be called when a transfer is removed.
     *
     * @param[in] transferId The transfer's ID
     */
    void onTransferRemoved(const QUuid& transferId);

    /**
     * Slot to be called when a transfer's data changes.
     */
    void onTransferDataChanged();

private:
    const TransferManager* _manager{nullptr};  ///< Pointer to the active TransferManager instance, if any
    QVector<QUuid> _transferIds;               ///< List of transfer IDs
};
