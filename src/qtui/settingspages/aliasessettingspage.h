// SPDX-License-Identifier: GPL-2.0-or-later

#ifndef ALIASESSETTINGSPAGE_H
#define ALIASESSETTINGSPAGE_H

#include "aliasesmodel.h"
#include "settingspage.h"

#include "ui_aliasessettingspage.h"

class AliasesSettingsPage : public SettingsPage
{
    Q_OBJECT

public:
    AliasesSettingsPage(QWidget* parent = nullptr);

    inline bool hasDefaults() const override { return true; }
    inline bool needsCoreConnection() const override { return true; }

public slots:
    void save() override;
    void load() override;
    void defaults() override;

private slots:
    void enableDialog(bool);
    void deleteSelectedAlias();

private:
    Ui::AliasesSettingsPage ui;

    AliasesModel _aliasesModel;
};

#endif  // ALIASESSETTINGSPAGE_H
