// SPDX-License-Identifier: GPL-2.0-or-later

#include "aliasessettingspage.h"

#include <QHeaderView>
#include <QItemSelectionModel>

#include "icon.h"

AliasesSettingsPage::AliasesSettingsPage(QWidget* parent)
    : SettingsPage(tr("IRC"), tr("Aliases"), parent)
{
    ui.setupUi(this);
    ui.newAliasButton->setIcon(icon::get("list-add"));
    ui.deleteAliasButton->setIcon(icon::get("edit-delete"));

    ui.aliasesView->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui.aliasesView->setSelectionMode(QAbstractItemView::SingleSelection);
    ui.aliasesView->setAlternatingRowColors(true);
    ui.aliasesView->setTabKeyNavigation(false);
    ui.aliasesView->setModel(&_aliasesModel);
    // ui.aliasesView->setSortingEnabled(true);
    ui.aliasesView->verticalHeader()->hide();
    ui.aliasesView->horizontalHeader()->setStretchLastSection(true);

    connect(ui.newAliasButton, &QAbstractButton::clicked, &_aliasesModel, &AliasesModel::newAlias);
    connect(ui.deleteAliasButton, &QAbstractButton::clicked, this, &AliasesSettingsPage::deleteSelectedAlias);
    connect(&_aliasesModel, &AliasesModel::configChanged, this, &AliasesSettingsPage::setChangedState);
    connect(&_aliasesModel, &AliasesModel::modelReady, this, &AliasesSettingsPage::enableDialog);

    enableDialog(_aliasesModel.isReady());
}

void AliasesSettingsPage::load()
{
    if (_aliasesModel.hasConfigChanged())
        _aliasesModel.revert();
}

void AliasesSettingsPage::defaults()
{
    _aliasesModel.loadDefaults();
}

void AliasesSettingsPage::save()
{
    if (_aliasesModel.hasConfigChanged())
        _aliasesModel.commit();
}

void AliasesSettingsPage::enableDialog(bool enabled)
{
    ui.newAliasButton->setEnabled(enabled);
    ui.deleteAliasButton->setEnabled(enabled);
    setEnabled(enabled);
}

void AliasesSettingsPage::deleteSelectedAlias()
{
    if (!ui.aliasesView->selectionModel()->hasSelection())
        return;

    _aliasesModel.removeAlias(ui.aliasesView->selectionModel()->selectedIndexes()[0].row());
}
