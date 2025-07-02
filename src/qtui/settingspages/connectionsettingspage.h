// SPDX-License-Identifier: GPL-2.0-or-later

#ifndef CONNECTIONSETTINGSPAGE_H_
#define CONNECTIONSETTINGSPAGE_H_

#include "settings.h"
#include "settingspage.h"

#include "ui_connectionsettingspage.h"

class ConnectionSettingsPage : public SettingsPage
{
    Q_OBJECT

public:
    ConnectionSettingsPage(QWidget* parent = nullptr);

    bool hasDefaults() const override;
    bool needsCoreConnection() const override { return true; }

public slots:

private slots:
    void clientConnected();
    void clientDisconnected();
    void initDone();

private:
    QVariant loadAutoWidgetValue(const QString& widgetName) override;
    void saveAutoWidgetValue(const QString& widgetName, const QVariant& value) override;

    Ui::ConnectionSettingsPage ui;
};

#endif
