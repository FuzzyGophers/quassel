// SPDX-License-Identifier: GPL-2.0-or-later

#include "corealiasmanager.h"

#include "core.h"
#include "corenetwork.h"
#include "coresession.h"

CoreAliasManager::CoreAliasManager(CoreSession* parent)
    : AliasManager(parent)
{
    auto* session = qobject_cast<CoreSession*>(parent);
    if (!session) {
        qWarning() << "CoreAliasManager: unable to load Aliases. Parent is not a Coresession!";
        loadDefaults();
        return;
    }

    initSetAliases(Core::getUserSetting(session->user(), "Aliases").toMap());
    if (isEmpty())
        loadDefaults();

    // we store our settings whenever they change
    connect(this, &SyncableObject::updatedRemotely, this, &CoreAliasManager::save);
}

void CoreAliasManager::save() const
{
    auto* session = qobject_cast<CoreSession*>(parent());
    if (!session) {
        qWarning() << "CoreAliasManager: unable to save Aliases. Parent is not a Coresession!";
        return;
    }

    Core::setUserSetting(session->user(), "Aliases", initAliases());
}

const Network* CoreAliasManager::network(NetworkId id) const
{
    return qobject_cast<CoreSession*>(parent())->network(id);
}

void CoreAliasManager::loadDefaults()
{
    foreach (Alias alias, AliasManager::defaults()) {
        addAlias(alias.name, alias.expansion);
    }
}
