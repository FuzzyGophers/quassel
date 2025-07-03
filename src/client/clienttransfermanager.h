// SPDX-FileCopyrightText: 2005-2025 Quassel Project <devel@quassel-irc.org>
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

#include <QUuid>

#include "transfermanager.h"

class ClientTransferManager : public TransferManager
{
    Q_OBJECT

public:
    using TransferManager::TransferManager;

private slots:
    void setTransferIds(const QList<QUuid>& transferIds) override;
    void onCoreTransferAdded(const QUuid& uuid) override;
    void onTransferInitDone();
};
