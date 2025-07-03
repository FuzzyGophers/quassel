// SPDX-FileCopyrightText: 2005-2025 Quassel Project <devel@quassel-irc.org>
// SPDX-License-Identifier: GPL-2.0-or-later

#include "coreusersettings.h"

CoreUserSettings::CoreUserSettings(UserId uid)
    : CoreSettings(QString("CoreUser/%1").arg(uid.toInt()))
    , user(uid)
{
}

Identity CoreUserSettings::identity(IdentityId id) const
{
    QVariant v = localValue(QString("Identities/%1").arg(id.toInt()));
    if (v.canConvert<Identity>()) {
        return v.value<Identity>();
    }
    return Identity();
}

QList<IdentityId> CoreUserSettings::identityIds() const
{
    QList<IdentityId> res;
    foreach (QString id, localChildKeys("Identities")) {
        res << id.toInt();
    }
    return res;
}

void CoreUserSettings::storeIdentity(const Identity& identity)
{
    setLocalValue(QString("Identities/%1").arg(identity.id().toInt()), QVariant::fromValue(identity));
}

void CoreUserSettings::removeIdentity(IdentityId id)
{
    removeLocalKey(QString("Identities/%1").arg(id.toInt()));
}

void CoreUserSettings::setSessionState(const QVariant& data)
{
    setLocalValue("SessionState", data);
}

QVariant CoreUserSettings::sessionState(const QVariant& def) const
{
    return localValue("SessionState", def);
}

QVariantMap CoreUserSettings::sessionData() const
{
    QVariantMap res;
    foreach (QString key, localChildKeys(QString("SessionData"))) {
        res[key] = localValue(QString("SessionData/%1").arg(key));
    }
    return res;
}

void CoreUserSettings::setSessionValue(const QString& key, const QVariant& data)
{
    setLocalValue(QString("SessionData/%1").arg(key), data);
}

QVariant CoreUserSettings::sessionValue(const QString& key, const QVariant& def) const
{
    return localValue(QString("SessionData/%1").arg(key), def);
}
