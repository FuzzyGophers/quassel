// SPDX-FileCopyrightText: 2005-2025 Quassel Project <devel@quassel-irc.org>
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

#include "transfermanager.h"

class CoreTransfer;

class CoreTransferManager : public TransferManager
{
    Q_OBJECT

public:
    using TransferManager::TransferManager;

    // make available unprotected
    using TransferManager::addTransfer;
};
