// SPDX-FileCopyrightText: 2005-2025 Quassel Project <devel@quassel-irc.org>
// SPDX-License-Identifier: GPL-2.0-or-later

#include "coresessionwidget.h"

#include <QDateTime>

#include "client.h"
#include "util.h"

CoreSessionWidget::CoreSessionWidget(QWidget* parent)
    : QWidget(parent)
{
    ui.setupUi(this);
    connect(ui.disconnectButton, &QPushButton::released, this, &CoreSessionWidget::onDisconnectClicked);
}

void CoreSessionWidget::setData(QMap<QString, QVariant> map)
{
    ui.sessionGroup->setTitle(map["remoteAddress"].toString());
    ui.labelLocation->setText(map["location"].toString());
    ui.labelClient->setText(map["clientVersion"].toString());
    if (map["clientVersionDate"].toString().isEmpty()) {
        ui.labelVersionDate->setText(QString("<i>%1</i>").arg(tr("Unknown date")));
    }
    else {
        QDateTime versionDate = QDateTime::fromString(map["clientVersionDate"].toString(), Qt::ISODate);
        ui.labelVersionDate->setText(QLocale().toString(versionDate, QLocale::ShortFormat));
    }
    QDateTime connectedSince = map["connectedSince"].toDateTime().toLocalTime();
    ui.labelUptime->setText(QLocale().toString(connectedSince, QLocale::ShortFormat));
    if (map["location"].toString().isEmpty()) {
        ui.labelLocation->hide();
        ui.labelLocationTitle->hide();
    }
    ui.labelSecure->setText(map["secure"].toBool() ? tr("Yes") : tr("No"));

    auto features = Quassel::Features{map["featureList"].toStringList(), static_cast<Quassel::LegacyFeatures>(map["features"].toUInt())};
    if (features.isEnabled(Quassel::Feature::RemoteDisconnect)) {
        // Both client and core support it, enable the button
        ui.disconnectButton->setEnabled(true);
        ui.disconnectButton->setToolTip(tr("End the client's session, disconnecting it"));
    }
    else {
        // Either core or client doesn't support it, disable the option
        ui.disconnectButton->setEnabled(false);
        ui.disconnectButton->setToolTip(
            QString("<p>%1</p><p><b>%2</b></p>")
                .arg(tr("End the client's session, disconnecting it"), tr("This client does not support being remotely disconnected")));
    }

    bool success = false;
    _peerId = map["id"].toInt(&success);
    if (!success)
        _peerId = -1;
}

void CoreSessionWidget::onDisconnectClicked()
{
    // Don't allow the End Session button to be spammed; Quassel's protocol isn't lossy and it
    // should reach the destination eventually...
    ui.disconnectButton->setEnabled(false);
    ui.disconnectButton->setText(tr("Ending session..."));

    emit disconnectClicked(_peerId);
}
