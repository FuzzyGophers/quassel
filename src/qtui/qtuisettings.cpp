// SPDX-License-Identifier: GPL-2.0-or-later

#include "qtuisettings.h"

QtUiSettings::QtUiSettings()
    : UiSettings("QtUi")
{}

QtUiSettings::QtUiSettings(const QString& subGroup)
    : UiSettings(QString("QtUi/%1").arg(subGroup))
{}

/***********************************************************************/

QtUiStyleSettings::QtUiStyleSettings()
    : UiSettings("QtUiStyle")
{}

QtUiStyleSettings::QtUiStyleSettings(const QString& subGroup)
    : UiSettings(QString("QtUiStyle/%1").arg(subGroup))
{}

/***********************************************************************/

WarningsSettings::WarningsSettings()
    : UiSettings("Warnings")
{}

bool WarningsSettings::showWarning(const QString& key) const
{
    return localValue(key, true).toBool();
}

void WarningsSettings::setShowWarning(const QString& key, bool show)
{
    setLocalValue(key, show);
}
