// SPDX-FileCopyrightText: 2005-2025 Quassel Project <devel@quassel-irc.org>
// SPDX-License-Identifier: GPL-2.0-or-later

#include "clienttransfermanager.h"

#include "client.h"
#include "clienttransfer.h"

void ClientTransferManager::setTransferIds(const QList<QUuid>& transferIds)
{
    for (auto&& id : transferIds) {
        onCoreTransferAdded(id);
    }
}

void ClientTransferManager::onCoreTransferAdded(const QUuid& uuid)
{
    if (uuid.isNull()) {
        qWarning() << Q_FUNC_INFO << "Invalid transfer uuid" << uuid.toString();
        return;
    }

    auto transfer = new ClientTransfer(uuid, this);
    connect(transfer, &SyncableObject::initDone, this, &ClientTransferManager::onTransferInitDone);  // we only want to add initialized transfers
    Client::signalProxy()->synchronize(transfer);
}

void ClientTransferManager::onTransferInitDone()
{
    auto* transfer = qobject_cast<Transfer*>(sender());
    Q_ASSERT(transfer);
    addTransfer(transfer);
}
