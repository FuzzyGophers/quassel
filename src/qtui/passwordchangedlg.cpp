// SPDX-License-Identifier: GPL-2.0-or-later

#include "passwordchangedlg.h"

#include <QMessageBox>
#include <QPushButton>

#include "client.h"

PasswordChangeDlg::PasswordChangeDlg(QWidget* parent)
    : QDialog(parent)
{
    ui.setupUi(this);

    CoreAccount account = Client::currentCoreAccount();
    ui.infoLabel->setText(tr("This changes the password for your username <b>%1</b> "
                             "on the Quassel Core running at <b>%2</b>.")
                              .arg(account.user(), account.hostName()));

    connect(ui.oldPasswordEdit, &QLineEdit::textChanged, this, &PasswordChangeDlg::inputChanged);
    connect(ui.newPasswordEdit, &QLineEdit::textChanged, this, &PasswordChangeDlg::inputChanged);
    connect(ui.confirmPasswordEdit, &QLineEdit::textChanged, this, &PasswordChangeDlg::inputChanged);
    connect(ui.buttonBox, &QDialogButtonBox::accepted, this, &PasswordChangeDlg::changePassword);

    connect(Client::instance(), &Client::passwordChanged, this, &PasswordChangeDlg::passwordChanged);

    ui.buttonBox->button(QDialogButtonBox::Ok)->setEnabled(false);
}

void PasswordChangeDlg::inputChanged()
{
    bool ok = !ui.oldPasswordEdit->text().isEmpty() && !ui.newPasswordEdit->text().isEmpty()
              && ui.newPasswordEdit->text() == ui.confirmPasswordEdit->text();
    ui.buttonBox->button(QDialogButtonBox::Ok)->setEnabled(ok);
}

void PasswordChangeDlg::changePassword()
{
    ui.buttonBox->button(QDialogButtonBox::Ok)->setEnabled(false);
    Client::changePassword(ui.oldPasswordEdit->text(), ui.newPasswordEdit->text());
}

void PasswordChangeDlg::passwordChanged(bool success)
{
    if (!success) {
        QMessageBox box(QMessageBox::Warning, tr("Password Not Changed"), tr("<b>Password change failed</b>"), QMessageBox::Ok, this);
        box.setInformativeText(
            tr("The core reported an error when trying to change your password. Make sure you entered your old password correctly!"));
        box.exec();
    }
    else {
        accept();
    }
}
