// SPDX-FileCopyrightText: 2005-2025 Quassel Project <devel@quassel-irc.org>
// SPDX-License-Identifier: GPL-2.0-or-later

#include "settingspagedlg.h"

#include <QMessageBox>
#include <QPushButton>

#include "icon.h"

SettingsPageDlg::SettingsPageDlg(SettingsPage* page, QWidget* parent)
    : QDialog(parent)
{
    ui.setupUi(this);
    _currentPage = page;
    page->setParent(this);

    // make it look more native under Mac OS X:
    setWindowFlags(Qt::Sheet);

    ui.pageTitle->setText(page->title());
    setWindowTitle(tr("Configure %1").arg(page->title()));
    setWindowIcon(icon::get("configure"));

    // make the scrollarea behave sanely
    ui.settingsFrame->setWidgetResizable(true);
    ui.settingsFrame->setWidget(page);

    updateGeometry();

    connect(page, &SettingsPage::changed, this, &SettingsPageDlg::setButtonStates);
    connect(ui.buttonBox, &QDialogButtonBox::clicked, this, &SettingsPageDlg::buttonClicked);
    page->load();
    setButtonStates();
}

SettingsPage* SettingsPageDlg::currentPage() const
{
    return _currentPage;
}

void SettingsPageDlg::setButtonStates()
{
    SettingsPage* sp = currentPage();
    ui.buttonBox->button(QDialogButtonBox::Apply)->setEnabled(sp && sp->hasChanged());
    ui.buttonBox->button(QDialogButtonBox::Reset)->setEnabled(sp && sp->hasChanged());
    ui.buttonBox->button(QDialogButtonBox::RestoreDefaults)->setEnabled(sp && sp->hasDefaults());
}

void SettingsPageDlg::buttonClicked(QAbstractButton* button)
{
    switch (ui.buttonBox->standardButton(button)) {
    case QDialogButtonBox::Ok:
        if (currentPage() && currentPage()->hasChanged()) {
            if (applyChanges())
                accept();
        }
        else
            accept();
        break;
    case QDialogButtonBox::Apply:
        applyChanges();
        break;
    case QDialogButtonBox::Cancel:
        undoChanges();
        reject();
        break;
    case QDialogButtonBox::Reset:
        reload();
        break;
    case QDialogButtonBox::RestoreDefaults:
        loadDefaults();
        break;
    default:
        break;
    }
}

bool SettingsPageDlg::applyChanges()
{
    if (!currentPage())
        return false;
    if (currentPage()->aboutToSave()) {
        currentPage()->save();
        return true;
    }
    return false;
}

void SettingsPageDlg::undoChanges()
{
    if (currentPage()) {
        currentPage()->load();
    }
}

void SettingsPageDlg::reload()
{
    if (!currentPage())
        return;
    int ret = QMessageBox::question(this,
                                    tr("Reload Settings"),
                                    tr("Do you like to reload the settings, undoing your changes on this page?"),
                                    QMessageBox::Yes | QMessageBox::No,
                                    QMessageBox::No);
    if (ret == QMessageBox::Yes) {
        currentPage()->load();
    }
}

void SettingsPageDlg::loadDefaults()
{
    if (!currentPage())
        return;
    int ret = QMessageBox::question(this,
                                    tr("Restore Defaults"),
                                    tr("Do you like to restore the default values for this page?"),
                                    QMessageBox::RestoreDefaults | QMessageBox::Cancel,
                                    QMessageBox::Cancel);
    if (ret == QMessageBox::RestoreDefaults) {
        currentPage()->defaults();
    }
}
