// SPDX-FileCopyrightText: 2005-2025 Quassel Project <devel@quassel-irc.org>
// SPDX-License-Identifier: GPL-2.0-or-later

#include "clientignorelistmanager.h"

ClientIgnoreListManager::ClientIgnoreListManager(QObject* parent)
    : IgnoreListManager(parent)
{
    connect(this, &SyncableObject::updatedRemotely, this, &ClientIgnoreListManager::ignoreListChanged);
}

bool ClientIgnoreListManager::pureMatch(const IgnoreListItem& item, const QString& string) const
{
    return (item.contentsMatcher().match(string));
}

QMap<QString, bool> ClientIgnoreListManager::matchingRulesForHostmask(const QString& hostmask,
                                                                      const QString& network,
                                                                      const QString& channel) const
{
    QMap<QString, bool> result;
    foreach (IgnoreListItem item, ignoreList()) {
        if (item.type() == SenderIgnore && pureMatch(item, hostmask)
            && ((network.isEmpty() && channel.isEmpty()) || item.scope() == GlobalScope
                || (item.scope() == NetworkScope && item.scopeRuleMatcher().match(network))
                || (item.scope() == ChannelScope && item.scopeRuleMatcher().match(channel)))) {
            result[item.contents()] = item.isEnabled();
            // qDebug() << "matchingRulesForHostmask found: " << item.contents()
            //         << "is active: " << item.isActive;
        }
    }
    return result;
}
