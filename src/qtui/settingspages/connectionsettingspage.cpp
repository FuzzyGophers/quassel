// SPDX-FileCopyrightText: 2005-2025 Quassel Project <devel@quassel-irc.org>
// SPDX-License-Identifier: GPL-2.0-or-later

#include "connectionsettingspage.h"

#include "client.h"
#include "networkconfig.h"

ConnectionSettingsPage::ConnectionSettingsPage(QWidget* parent)
    : SettingsPage(tr("IRC"), QString(), parent)
{
    ui.setupUi(this);
    initAutoWidgets();

    connect(Client::instance(), &Client::connected, this, &ConnectionSettingsPage::clientConnected);
    connect(Client::instance(), &Client::disconnected, this, &ConnectionSettingsPage::clientDisconnected);

    setEnabled(false);
    if (Client::isConnected())
        clientConnected();
}

void ConnectionSettingsPage::clientConnected()
{
    if (Client::networkConfig()->isInitialized())
        initDone();
    else
        connect(Client::networkConfig(), &SyncableObject::initDone, this, &ConnectionSettingsPage::initDone);
}

void ConnectionSettingsPage::clientDisconnected()
{
    setEnabled(false);
    setChangedState(false);
}

void ConnectionSettingsPage::initDone()
{
    setEnabled(true);
}

bool ConnectionSettingsPage::hasDefaults() const
{
    return true;
}

QVariant ConnectionSettingsPage::loadAutoWidgetValue(const QString& widgetName)
{
    if (!isEnabled())
        return QVariant();
    NetworkConfig* config = Client::networkConfig();
    if (widgetName == "pingTimeoutEnabled")
        return config->pingTimeoutEnabled();
    if (widgetName == "pingInterval")
        return config->pingInterval();
    if (widgetName == "maxPingCount")
        return config->maxPingCount();
    if (widgetName == "autoWhoEnabled")
        return config->autoWhoEnabled();
    if (widgetName == "autoWhoInterval")
        return config->autoWhoInterval();
    if (widgetName == "autoWhoNickLimit")
        return config->autoWhoNickLimit();
    if (widgetName == "autoWhoDelay")
        return config->autoWhoDelay();
    if (widgetName == "standardCtcp")
        return config->standardCtcp();

    return SettingsPage::loadAutoWidgetValue(widgetName);
}

void ConnectionSettingsPage::saveAutoWidgetValue(const QString& widgetName, const QVariant& value)
{
    if (!isEnabled())
        return;
    NetworkConfig* config = Client::networkConfig();
    if (widgetName == "pingTimeoutEnabled")
        config->requestSetPingTimeoutEnabled(value.toBool());
    else if (widgetName == "pingInterval")
        config->requestSetPingInterval(value.toInt());
    else if (widgetName == "maxPingCount")
        config->requestSetMaxPingCount(value.toInt());
    else if (widgetName == "autoWhoEnabled")
        config->requestSetAutoWhoEnabled(value.toBool());
    else if (widgetName == "autoWhoInterval")
        config->requestSetAutoWhoInterval(value.toInt());
    else if (widgetName == "autoWhoNickLimit")
        config->requestSetAutoWhoNickLimit(value.toInt());
    else if (widgetName == "autoWhoDelay")
        config->requestSetAutoWhoDelay(value.toInt());
    else if (widgetName == "standardCtcp")
        config->requestSetStandardCtcp(value.toBool());

    else
        SettingsPage::saveAutoWidgetValue(widgetName, value);
}
