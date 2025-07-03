// SPDX-FileCopyrightText: 2005-2025 Quassel Project <devel@quassel-irc.org>
// SPDX-License-Identifier: GPL-2.0-or-later

#include "corehighlightrulemanager.h"

#include "core.h"
#include "coresession.h"

constexpr auto settingsKey = "HighlightRuleList";

CoreHighlightRuleManager::CoreHighlightRuleManager(CoreSession* session)
    : HighlightRuleManager(session)
    , _coreSession{session}
{
    // Load config from database if it exists
    auto configMap = Core::getUserSetting(session->user(), settingsKey).toMap();
    if (!configMap.isEmpty())
        update(configMap);
    // Otherwise, we just use the defaults initialized in the base class

    // We store our settings whenever they change
    connect(this, &SyncableObject::updatedRemotely, this, &CoreHighlightRuleManager::save);
}

void CoreHighlightRuleManager::save()
{
    Core::setUserSetting(_coreSession->user(), settingsKey, toVariantMap());
}

bool CoreHighlightRuleManager::match(const RawMessage& msg, const QString& currentNick, const QStringList& identityNicks)
{
    return match(msg.networkId, msg.text, msg.sender, msg.type, msg.flags, msg.target, currentNick, identityNicks);
}
