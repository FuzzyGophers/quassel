// SPDX-FileCopyrightText: 2005-2025 Quassel Project <devel@quassel-irc.org>
// SPDX-License-Identifier: GPL-2.0-or-later

#ifndef CORECONNECTDLG_H
#define CORECONNECTDLG_H

#include <QDialog>

#include "coreaccount.h"

#include "ui_coreconnectauthdlg.h"

class CoreAccountSettingsPage;

class CoreConnectDlg : public QDialog
{
    Q_OBJECT

public:
    CoreConnectDlg(QWidget* parent = nullptr);
    AccountId selectedAccount() const;

    void accept() override;

private:
    CoreAccountSettingsPage* _settingsPage;
};

class CoreConnectAuthDlg : public QDialog
{
    Q_OBJECT

public:
    CoreConnectAuthDlg(CoreAccount* account, QWidget* parent = nullptr);

    void accept() override;

private slots:
    void setButtonStates();

private:
    Ui::CoreConnectAuthDlg ui;
    CoreAccount* _account;
};

#endif
