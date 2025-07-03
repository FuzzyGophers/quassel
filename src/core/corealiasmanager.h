// SPDX-FileCopyrightText: 2005-2025 Quassel Project <devel@quassel-irc.org>
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

#include "aliasmanager.h"

class CoreSession;

class CoreAliasManager : public AliasManager
{
    Q_OBJECT

public:
    explicit CoreAliasManager(CoreSession* parent);

protected:
    const Network* network(NetworkId) const override;

private slots:
    void save() const;

private:
    void loadDefaults();
};
