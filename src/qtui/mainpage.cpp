// SPDX-License-Identifier: GPL-2.0-or-later

#include "mainpage.h"

#include <QImage>
#include <QLabel>
#include <QLayout>
#include <QPainter>
#include <QPushButton>

#include "client.h"
#include "coreconnectdlg.h"
#include "icon.h"

MainPage::MainPage(QWidget* parent)
    : QWidget(parent)
{
    auto* layout = new QVBoxLayout(this);
    layout->setAlignment(Qt::AlignCenter);
    QLabel* label = new QLabel(this);
    label->setPixmap(QPixmap(":/pics/quassel-logo.png"));
    layout->addWidget(label);

    if (Quassel::runMode() != Quassel::Monolithic) {
        _connectButton = new QPushButton(icon::get("network-connect"), tr("Connect to Core..."));
        _connectButton->setEnabled(Client::coreConnection()->state() == CoreConnection::Disconnected);

        connect(Client::coreConnection(), &CoreConnection::stateChanged, this, &MainPage::coreConnectionStateChanged);
        connect(_connectButton, &QAbstractButton::clicked, this, &MainPage::showCoreConnectionDlg);
        layout->addWidget(_connectButton);
    }
}

void MainPage::showCoreConnectionDlg()
{
    CoreConnectDlg dlg(this);
    if (dlg.exec() == QDialog::Accepted) {
        AccountId accId = dlg.selectedAccount();
        if (accId.isValid())
            Client::coreConnection()->connectToCore(accId);
    }
}

void MainPage::coreConnectionStateChanged()
{
    if (Client::coreConnection()->state() == CoreConnection::Disconnected) {
        _connectButton->setEnabled(true);
    }
    else {
        _connectButton->setDisabled(true);
    }
}
