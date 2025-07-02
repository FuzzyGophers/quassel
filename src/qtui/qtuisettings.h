// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

#include "uisettings.h"

class QtUiSettings : public UiSettings
{
public:
    QtUiSettings();
    QtUiSettings(const QString& subGroup);
};

class QtUiStyleSettings : public UiSettings
{
public:
    QtUiStyleSettings();
    QtUiStyleSettings(const QString& subGroup);
};

class WarningsSettings : public UiSettings
{
public:
    WarningsSettings();

    bool showWarning(const QString& key) const;
    void setShowWarning(const QString& key, bool show);
};
