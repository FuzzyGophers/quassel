// SPDX-FileCopyrightText: 2005-2025 Quassel Project <devel@quassel-irc.org>
// SPDX-License-Identifier: GPL-2.0-or-later

#ifndef BACKLOGSETTINGSPAGE_H
#define BACKLOGSETTINGSPAGE_H

#include <QHash>

#include "settingspage.h"

#include "ui_backlogsettingspage.h"

class BacklogSettingsPage : public SettingsPage
{
    Q_OBJECT

public:
    BacklogSettingsPage(QWidget* parent = nullptr);

    inline QString settingsKey() const override { return "Backlog"; }
    bool hasDefaults() const override;

public slots:
    void save() override;
    void load() override;
    void defaults() override;

private slots:
    void widgetHasChanged();

private:
    Ui::BacklogSettingsPage ui;
};

#endif
