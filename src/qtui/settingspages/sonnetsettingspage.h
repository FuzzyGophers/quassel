// SPDX-FileCopyrightText: 2005-2025 Quassel Project <devel@quassel-irc.org>
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

#include <Sonnet/ConfigWidget>

#include "settingspage.h"

//! A settings page for configuring the Sonnet spell-checking engine
class SonnetSettingsPage : public SettingsPage
{
    Q_OBJECT

public:
    SonnetSettingsPage(QWidget* parent = nullptr);

    bool hasDefaults() const override;

public slots:
    void save() override;
    void load() override;
    void defaults() override;

private slots:
    void widgetHasChanged();

private:
    Sonnet::ConfigWidget* _configWidget;
};
