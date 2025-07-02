// SPDX-License-Identifier: GPL-2.0-or-later

#ifndef INPUTLINESETTINGSPAGE_H_
#define INPUTLINESETTINGSPAGE_H_

#include "settingspage.h"

#include "ui_inputwidgetsettingspage.h"

class InputWidgetSettingsPage : public SettingsPage
{
    Q_OBJECT

public:
    InputWidgetSettingsPage(QWidget* parent = nullptr);

    inline bool hasDefaults() const override { return true; }

private:
    Ui::InputWidgetSettingsPage ui;

    inline QString settingsKey() const override { return QString("InputWidget"); }
};

#endif
