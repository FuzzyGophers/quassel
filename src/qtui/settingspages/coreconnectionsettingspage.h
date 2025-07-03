// SPDX-FileCopyrightText: 2005-2025 Quassel Project <devel@quassel-irc.org>
// SPDX-License-Identifier: GPL-2.0-or-later

#ifndef COREACCOUNTSETTINGSPAGE_H
#define COREACCOUNTSETTINGSPAGE_H

#include "clientsettings.h"
#include "settingspage.h"

#include "ui_coreconnectionsettingspage.h"

class CoreConnectionSettingsPage : public SettingsPage
{
    Q_OBJECT

public:
    CoreConnectionSettingsPage(QWidget* parent = nullptr);

    inline bool hasDefaults() const override { return true; }

public slots:
    void save() override;
    void load() override;
    void defaults() override;

signals:

private slots:
    void widgetHasChanged();

private:
    Ui::CoreConnectionSettingsPage ui;
    CoreConnectionSettings::NetworkDetectionMode _detectionMode;

    void setRadioButtons(CoreConnectionSettings::NetworkDetectionMode mode);
    CoreConnectionSettings::NetworkDetectionMode modeFromRadioButtons() const;

    inline QString settingsKey() const override { return QString("CoreConnection"); }
};

#endif
