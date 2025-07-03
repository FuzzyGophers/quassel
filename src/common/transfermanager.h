// SPDX-FileCopyrightText: 2005-2025 Quassel Project <devel@quassel-irc.org>
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

#include "common-export.h"

#include <QHash>
#include <QList>
#include <QUuid>
#include <QMetaType>

#include "syncableobject.h"

class Transfer;

class COMMON_EXPORT TransferManager : public SyncableObject
{
    Q_OBJECT
    SYNCABLE_OBJECT

    Q_PROPERTY(TransferManager::TransferIdList transferIds READ transferIds WRITE setTransferIds)

public:
    using TransferIdList = QList<QUuid>;

    TransferManager(QObject* parent = nullptr);

    Transfer* transfer(const QUuid& uuid) const;
    TransferIdList transferIds() const;

signals:
    void transferAdded(const QUuid& uuid);
    void transferRemoved(const QUuid& uuid);

protected:
    void addTransfer(Transfer* transfer);
    void removeTransfer(const QUuid& uuid);

protected slots:
    virtual void setTransferIds(const TransferIdList& transferIds) { Q_UNUSED(transferIds); }
    virtual void onCoreTransferAdded(const QUuid& transferId) { Q_UNUSED(transferId); }

private:
    QHash<QUuid, Transfer*> _transfers;
};

QDataStream& operator<<(QDataStream& out, const TransferManager::TransferIdList& transferIds);
QDataStream& operator>>(QDataStream& in, TransferManager::TransferIdList& transferIds);

Q_DECLARE_METATYPE(TransferManager::TransferIdList)
