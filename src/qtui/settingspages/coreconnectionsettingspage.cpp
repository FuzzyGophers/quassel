// SPDX-License-Identifier: GPL-2.0-or-later

#include "coreconnectionsettingspage.h"

#include <QNetworkInformation>

CoreConnectionSettingsPage::CoreConnectionSettingsPage(QWidget* parent)
    : SettingsPage(tr("Remote Cores"), tr("Connection"), parent)
{
    ui.setupUi(this);

    initAutoWidgets();

    connect(ui.useQNetworkInformation, &QAbstractButton::toggled, this, &CoreConnectionSettingsPage::widgetHasChanged);
    connect(ui.usePingTimeout, &QAbstractButton::toggled, this, &CoreConnectionSettingsPage::widgetHasChanged);
    connect(ui.useNoTimeout, &QAbstractButton::toggled, this, &CoreConnectionSettingsPage::widgetHasChanged);
}

void CoreConnectionSettingsPage::widgetHasChanged()
{
    bool hasChanged = false;
    CoreConnectionSettings::NetworkDetectionMode mode = modeFromRadioButtons();
    if (mode != _detectionMode)
        hasChanged = true;

    setChangedState(hasChanged);
}

void CoreConnectionSettingsPage::defaults()
{
    setRadioButtons(CoreConnectionSettings::UseQNetworkInformation);

    SettingsPage::defaults();
}

void CoreConnectionSettingsPage::load()
{
    CoreConnectionSettings s;
    _detectionMode = s.networkDetectionMode();
    setRadioButtons(_detectionMode);
    SettingsPage::load();
}

void CoreConnectionSettingsPage::save()
{
    _detectionMode = modeFromRadioButtons();
    CoreConnectionSettings s;
    s.setNetworkDetectionMode(_detectionMode);
    SettingsPage::save();
}

void CoreConnectionSettingsPage::setRadioButtons(CoreConnectionSettings::NetworkDetectionMode mode)
{
    switch (mode) {
    case CoreConnectionSettings::UseQNetworkInformation:
        ui.useQNetworkInformation->setChecked(true);
        break;
    case CoreConnectionSettings::UsePingTimeout:
        ui.usePingTimeout->setChecked(true);
        break;
    default:
        ui.useNoTimeout->setChecked(true);
    }
}

CoreConnectionSettings::NetworkDetectionMode CoreConnectionSettingsPage::modeFromRadioButtons() const
{
    if (ui.useQNetworkInformation->isChecked())
        return CoreConnectionSettings::UseQNetworkInformation;
    if (ui.usePingTimeout->isChecked())
        return CoreConnectionSettings::UsePingTimeout;

    return CoreConnectionSettings::NoActiveDetection;
}
