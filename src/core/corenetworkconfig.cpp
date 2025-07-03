// SPDX-FileCopyrightText: 2005-2025 Quassel Project <devel@quassel-irc.org>
// SPDX-License-Identifier: GPL-2.0-or-later

#include "corenetworkconfig.h"

#include "core.h"
#include "coresession.h"

CoreNetworkConfig::CoreNetworkConfig(const QString& objectName, CoreSession* session)
    : NetworkConfig(objectName, session)
{
    setAllowClientUpdates(true);

    if (!session) {
        qWarning() << Q_FUNC_INFO << "No CoreSession set, cannot load network configuration!";
        return;
    }

    fromVariantMap(Core::getUserSetting(session->user(), objectName).toMap());
}

void CoreNetworkConfig::save()
{
    auto* session = qobject_cast<CoreSession*>(parent());
    if (!session) {
        qWarning() << Q_FUNC_INFO << "No CoreSession set, cannot save network configuration!";
        return;
    }

    Core::setUserSetting(session->user(), objectName(), toVariantMap());
}
