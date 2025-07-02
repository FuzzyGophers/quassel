// SPDX-License-Identifier: GPL-2.0-or-later

#include "coresettings.h"

#include "quassel.h"

CoreSettings::CoreSettings(QString group)
    : Settings(std::move(group), Quassel::buildInfo().coreApplicationName)
{}

void CoreSettings::setStorageSettings(const QVariant& data)
{
    setLocalValue("StorageSettings", data);
}

QVariant CoreSettings::storageSettings(const QVariant& def) const
{
    return localValue("StorageSettings", def);
}

void CoreSettings::setAuthSettings(const QVariant& data)
{
    setLocalValue("AuthSettings", data);
}

QVariant CoreSettings::authSettings(const QVariant& def) const
{
    return localValue("AuthSettings", def);
}

// FIXME remove
QVariant CoreSettings::oldDbSettings() const
{
    return localValue("DatabaseSettings");
}

void CoreSettings::setCoreState(const QVariant& data)
{
    setLocalValue("CoreState", data);
}

QVariant CoreSettings::coreState(const QVariant& def) const
{
    return localValue("CoreState", def);
}
