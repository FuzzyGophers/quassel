// SPDX-FileCopyrightText: 2005-2025 Quassel Project <devel@quassel-irc.org>
// SPDX-License-Identifier: GPL-2.0-or-later

#include "clientaliasmanager.h"

#include "client.h"

ClientAliasManager::ClientAliasManager(QObject* parent)
    : AliasManager(parent)
{
}

const Network* ClientAliasManager::network(NetworkId id) const
{
    return Client::network(id);
}
