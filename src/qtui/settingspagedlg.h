// SPDX-FileCopyrightText: 2005-2025 Quassel Project <devel@quassel-irc.org>
// SPDX-License-Identifier: GPL-2.0-or-later

#ifndef SETTINGSPAGEDLG_H
#define SETTINGSPAGEDLG_H

#include <QDialog>

#include "settingspage.h"

#include "ui_settingspagedlg.h"

class SettingsPageDlg : public QDialog
{
    Q_OBJECT
public:
    SettingsPageDlg(SettingsPage* page, QWidget* parent = nullptr);

    SettingsPage* currentPage() const;

private slots:
    void buttonClicked(QAbstractButton*);
    bool applyChanges();
    void undoChanges();
    void reload();
    void loadDefaults();
    void setButtonStates();

private:
    Ui::SettingsPageDlg ui;

    SettingsPage* _currentPage;
};

#endif
