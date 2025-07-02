// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

#include <QDialog>

#include "ui_passwordchangedlg.h"

class PasswordChangeDlg : public QDialog
{
    Q_OBJECT

public:
    PasswordChangeDlg(QWidget* parent = nullptr);

private slots:
    void inputChanged();
    void changePassword();
    void passwordChanged(bool success);

private:
    Ui::PasswordChangeDlg ui;
    QString _newPassword;
};
