// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

#include <QVariantMap>

#include "coresettings.h"
#include "identity.h"
#include "network.h"
#include "types.h"

class CoreUserSettings : public CoreSettings
{
public:
    CoreUserSettings(UserId user);

    Identity identity(IdentityId id) const;
    QList<IdentityId> identityIds() const;
    void storeIdentity(const Identity& identity);
    void removeIdentity(IdentityId id);

    void setSessionState(const QVariant& data);
    QVariant sessionState(const QVariant& def = {}) const;

private:
    // this stuff should only be accessed by CoreSession!
    QVariantMap sessionData() const;
    QVariant sessionValue(const QString& key, const QVariant& def = {}) const;
    void setSessionValue(const QString& key, const QVariant& value);

    UserId user;

    friend class CoreSession;
};
