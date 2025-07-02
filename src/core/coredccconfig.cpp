// SPDX-License-Identifier: GPL-2.0-or-later

#include "coredccconfig.h"

#include "core.h"
#include "coresession.h"

constexpr auto settingsKey = "DccConfig";

CoreDccConfig::CoreDccConfig(CoreSession* session)
    : DccConfig(session)
    , _coreSession{session}
{
    // Load config from database if it exists
    auto configMap = Core::getUserSetting(session->user(), settingsKey).toMap();
    if (!configMap.isEmpty())
        update(configMap);
    // Otherwise, we just use the defaults initialized in the base class

    // We store our settings whenever they change
    connect(this, &SyncableObject::updatedRemotely, this, &CoreDccConfig::save);
}

void CoreDccConfig::save()
{
    Core::setUserSetting(_coreSession->user(), settingsKey, toVariantMap());
}
