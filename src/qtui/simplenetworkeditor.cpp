// SPDX-FileCopyrightText: 2005-2025 Quassel Project <devel@quassel-irc.org>
// SPDX-License-Identifier: GPL-2.0-or-later

#include "simplenetworkeditor.h"

#include "icon.h"
#include "networkssettingspage.h"

SimpleNetworkEditor::SimpleNetworkEditor(QWidget* parent)
    : QWidget(parent)
{
    ui.setupUi(this);

    ui.addServer->setIcon(icon::get("list-add"));
    ui.deleteServer->setIcon(icon::get("edit-delete"));
    ui.editServer->setIcon(icon::get("configure"));
    ui.upServer->setIcon(icon::get("go-up"));
    ui.downServer->setIcon(icon::get("go-down"));

    connect(ui.networkNameEdit, &QLineEdit::textEdited, this, &SimpleNetworkEditor::widgetHasChanged);
    connect(ui.channelList, &QTextEdit::textChanged, this, &SimpleNetworkEditor::widgetHasChanged);
}

void SimpleNetworkEditor::setWidgetStates()
{
    if (ui.serverList->selectedItems().count()) {
        ui.editServer->setEnabled(true);
        ui.deleteServer->setEnabled(true);
        ui.upServer->setEnabled(ui.serverList->currentRow() > 0);
        ui.downServer->setEnabled(ui.serverList->currentRow() < ui.serverList->count() - 1);
    }
    else {
        ui.editServer->setEnabled(false);
        ui.deleteServer->setEnabled(false);
        ui.upServer->setEnabled(false);
        ui.downServer->setEnabled(false);
    }
}

void SimpleNetworkEditor::displayNetworkInfo(const NetworkInfo& networkInfo)
{
    _networkInfo = networkInfo;

    ui.serverList->clear();
    foreach (Network::Server server, _networkInfo.serverList) {
        QListWidgetItem* item = new QListWidgetItem(QString("%1:%2").arg(server.host).arg(server.port));
        if (server.useSsl)
            item->setIcon(icon::get("document-encrypt"));
        ui.serverList->addItem(item);
    }

    ui.networkNameEdit->setText(_networkInfo.networkName);
    setWidgetStates();
}

void SimpleNetworkEditor::saveToNetworkInfo(NetworkInfo& networkInfo)
{
    _networkInfo.networkName = ui.networkNameEdit->text();
    networkInfo = _networkInfo;
}

QStringList SimpleNetworkEditor::defaultChannels() const
{
    return ui.channelList->toPlainText().split("\n", Qt::SkipEmptyParts);
}

void SimpleNetworkEditor::setDefaultChannels(const QStringList& channels)
{
    ui.channelList->setPlainText(channels.join("\n"));
}

void SimpleNetworkEditor::on_serverList_itemSelectionChanged()
{
    setWidgetStates();
}

void SimpleNetworkEditor::on_addServer_clicked()
{
    ServerEditDlg dlg(Network::Server(), this);
    if (dlg.exec() == QDialog::Accepted) {
        _networkInfo.serverList.append(dlg.serverData());
        displayNetworkInfo(_networkInfo);
        ui.serverList->setCurrentRow(ui.serverList->count() - 1);
        emit widgetHasChanged();
    }
}

void SimpleNetworkEditor::on_editServer_clicked()
{
    int cur = ui.serverList->currentRow();
    ServerEditDlg dlg(_networkInfo.serverList[cur], this);
    if (dlg.exec() == QDialog::Accepted) {
        _networkInfo.serverList[cur] = dlg.serverData();
        displayNetworkInfo(_networkInfo);
        ui.serverList->setCurrentRow(cur);
        emit widgetHasChanged();
    }
}

void SimpleNetworkEditor::on_deleteServer_clicked()
{
    int cur = ui.serverList->currentRow();
    _networkInfo.serverList.removeAt(cur);
    displayNetworkInfo(_networkInfo);
    ui.serverList->setCurrentRow(qMin(cur, ui.serverList->count() - 1));
    emit widgetHasChanged();
}

void SimpleNetworkEditor::on_upServer_clicked()
{
    int cur = ui.serverList->currentRow();
    Network::Server server = _networkInfo.serverList.takeAt(cur);
    _networkInfo.serverList.insert(cur - 1, server);
    displayNetworkInfo(_networkInfo);
    ui.serverList->setCurrentRow(cur - 1);
    emit widgetHasChanged();
}

void SimpleNetworkEditor::on_downServer_clicked()
{
    int cur = ui.serverList->currentRow();
    Network::Server server = _networkInfo.serverList.takeAt(cur);
    _networkInfo.serverList.insert(cur + 1, server);
    displayNetworkInfo(_networkInfo);
    ui.serverList->setCurrentRow(cur + 1);
    emit widgetHasChanged();
}
