// SPDX-License-Identifier: GPL-2.0-or-later

#include "sonnetsettingspage.h"

#include <QVBoxLayout>

#include "qtui.h"

SonnetSettingsPage::SonnetSettingsPage(QWidget* parent)
    : SettingsPage(tr("Interface"), tr("Spell Checking"), parent)
{
    auto* layout = new QVBoxLayout(this);
    _configWidget = new Sonnet::ConfigWidget(this);
    layout->addWidget(_configWidget);
    connect(_configWidget, &Sonnet::ConfigWidget::configChanged, this, &SonnetSettingsPage::widgetHasChanged);
}

bool SonnetSettingsPage::hasDefaults() const
{
    return true;
}

void SonnetSettingsPage::defaults()
{
    _configWidget->slotDefault();
    widgetHasChanged();
}

void SonnetSettingsPage::load()
{
    SettingsPage::load();
}

void SonnetSettingsPage::save()
{
    _configWidget->save();
    SettingsPage::save();
}

void SonnetSettingsPage::widgetHasChanged()
{
    if (!hasChanged())
        setChangedState(true);
}
