// SPDX-License-Identifier: GPL-2.0-or-later

#ifndef TOPICWIDGETSETTINGSPAGE_H_
#define TOPICWIDGETSETTINGSPAGE_H_

#include "settingspage.h"

#include "ui_topicwidgetsettingspage.h"

class TopicWidgetSettingsPage : public SettingsPage
{
    Q_OBJECT

public:
    TopicWidgetSettingsPage(QWidget* parent = nullptr);

    inline bool hasDefaults() const override { return true; }

private:
    Ui::TopicWidgetSettingsPage ui;

    inline QString settingsKey() const override { return QString("TopicWidget"); }
};

#endif
