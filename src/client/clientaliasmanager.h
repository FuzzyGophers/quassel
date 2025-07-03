// SPDX-FileCopyrightText: 2005-2025 Quassel Project <devel@quassel-irc.org>
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

#include "client-export.h"

#include "aliasmanager.h"

class CLIENT_EXPORT ClientAliasManager : public AliasManager
{
    Q_OBJECT

public:
    explicit ClientAliasManager(QObject* parent = nullptr);

protected:
    const Network* network(NetworkId) const override;
};
