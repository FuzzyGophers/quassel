// SPDX-License-Identifier: GPL-2.0-or-later

#include "transfermanager.h"

#include "transfer.h"

TransferManager::TransferManager(QObject* parent)
    : SyncableObject("TransferManager", parent)
{
}

Transfer* TransferManager::transfer(const QUuid& uuid) const
{
    return _transfers.value(uuid, nullptr);
}

TransferManager::TransferIdList TransferManager::transferIds() const
{
    return _transfers.keys();
}

void TransferManager::addTransfer(Transfer* transfer)
{
    QUuid uuid = transfer->uuid();
    if (_transfers.contains(uuid)) {
        qWarning() << "Cannot add the same file transfer twice!";
        transfer->deleteLater();
        return;
    }
    transfer->setParent(this);
    _transfers[uuid] = transfer;

    SYNC_OTHER(onCoreTransferAdded, ARG(uuid));
    emit transferAdded(uuid);
}

void TransferManager::removeTransfer(const QUuid& uuid)
{
    if (!_transfers.contains(uuid)) {
        qWarning() << "Can not find transfer" << uuid << "to remove!";
        return;
    }
    emit transferRemoved(uuid);
    auto transfer = _transfers.take(uuid);
    transfer->deleteLater();
}

QDataStream& operator<<(QDataStream& out, const TransferManager::TransferIdList& transferIds)
{
    out << static_cast<quint32>(transferIds.size());
    for (auto&& id : transferIds) {
        out << id;
    }
    return out;
}

QDataStream& operator>>(QDataStream& in, TransferManager::TransferIdList& transferIds)
{
    quint32 count;
    in >> count;
    transferIds.clear();
    transferIds.reserve(count);
    for (quint32 i = 0; i < count; ++i) {
        QUuid id;
        in >> id;
        transferIds << id;
    }
    return in;
}
