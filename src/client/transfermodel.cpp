// SPDX-License-Identifier: GPL-2.0-or-later

#include "transfermodel.h"

#include <array>

#include "transfermanager.h"

namespace {
constexpr int colCount{8};
}

int TransferModel::rowCount(const QModelIndex& index) const
{
    return index.isValid() ? 0 : _transferIds.size();
}

int TransferModel::columnCount(const QModelIndex& index) const
{
    return index.isValid() ? 0 : colCount;
}

QVariant TransferModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    static std::array<QString, colCount> headers = {
        {tr("Type"), tr("File"), tr("Status"), tr("Progress"), tr("Transferred"), tr("Speed"), tr("Peer"), tr("Peer Address")}};

    if (section < 0 || section >= columnCount() || orientation != Qt::Horizontal)
        return {};

    switch (role) {
    case Qt::DisplayRole:
        return headers[section];

    default:
        return {};
    }
}

QVariant TransferModel::data(const QModelIndex& index, int role) const
{
    if (!_manager)
        return {};
    if (index.column() < 0 || index.column() >= columnCount() || index.row() < 0 || index.row() >= rowCount())
        return {};

    auto t = _manager->transfer(_transferIds.at(index.row()));
    if (!t) {
        qWarning() << "Invalid transfer ID stored in TransferModel!";
        return {};
    }

    switch (role) {
    case Qt::DisplayRole:
        switch (index.column()) {
        case 0:  // Type
            return t->direction() == Transfer::Direction::Send ? tr("Send") : tr("Receive");
        case 1:  // File
            return t->fileName();
        case 2:  // Status
            return t->prettyStatus();
        case 3:  // Progress
            return (t->transferred() / t->fileSize()) * 100;
        case 4:                       // Transferred
            return t->transferred();  // TODO: use pretty units and show total
        case 5:                       // Speed
            return "n/a";             // TODO: fixme
        case 6:                       // Peer
            return t->nick();
        case 7:  // Peer Address
            return QString("%1.%2").arg(t->address().toString(), t->port());
        }
        break;

    default:
        return {};
    }

    return {};
}

void TransferModel::setManager(const TransferManager* manager)
{
    if (_manager) {
        disconnect(_manager, nullptr, this, nullptr);
        beginResetModel();
        _transferIds.clear();
        endResetModel();
    }

    _manager = manager;
    if (_manager) {
        connect(manager, &TransferManager::transferAdded, this, &TransferModel::onTransferAdded);
        connect(manager, &TransferManager::transferRemoved, this, &TransferModel::onTransferRemoved);
        for (auto&& transferId : _manager->transferIds()) {
            onTransferAdded(transferId);
        }
    }
}

void TransferModel::onTransferAdded(const QUuid& transferId)
{
    auto transfer = _manager->transfer(transferId);
    if (!transfer) {
        qWarning() << "Invalid transfer ID!";
        return;
    }

    // TODO Qt5: use new connection syntax to make things much less complicated
    connect(transfer, &Transfer::statusChanged, this, &TransferModel::onTransferDataChanged);
    connect(transfer, &Transfer::directionChanged, this, &TransferModel::onTransferDataChanged);
    connect(transfer, &Transfer::addressChanged, this, &TransferModel::onTransferDataChanged);
    connect(transfer, &Transfer::portChanged, this, &TransferModel::onTransferDataChanged);
    connect(transfer, &Transfer::fileNameChanged, this, &TransferModel::onTransferDataChanged);
    connect(transfer, &Transfer::fileSizeChanged, this, &TransferModel::onTransferDataChanged);
    connect(transfer, &Transfer::transferredChanged, this, &TransferModel::onTransferDataChanged);
    connect(transfer, &Transfer::nickChanged, this, &TransferModel::onTransferDataChanged);

    beginInsertRows({}, rowCount(), rowCount());
    _transferIds.append(transferId);
    endInsertRows();
}

void TransferModel::onTransferRemoved(const QUuid& transferId)
{
    // Check if the transfer object still exists, which means we still should disconnect
    auto transfer = _manager->transfer(transferId);
    if (transfer)
        disconnect(transfer, nullptr, this, nullptr);

    for (auto row = 0; row < _transferIds.size(); ++row) {
        if (_transferIds[row] == transferId) {
            beginRemoveRows(QModelIndex(), row, row);
            _transferIds.remove(row);
            endRemoveRows();
            break;
        }
    }
}

void TransferModel::onTransferDataChanged()
{
    auto transfer = qobject_cast<Transfer*>(sender());
    if (!transfer)
        return;

    const auto& transferId = transfer->uuid();
    for (auto row = 0; row < _transferIds.size(); ++row) {
        if (_transferIds[row] == transferId) {
            // TODO Qt5: use proper column
            auto topLeft = createIndex(row, 0);
            auto bottomRight = createIndex(row, columnCount());
            emit dataChanged(topLeft, bottomRight);
            break;
        }
    }
}
