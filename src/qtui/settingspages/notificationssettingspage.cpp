// SPDX-License-Identifier: GPL-2.0-or-later

#include "notificationssettingspage.h"

#include <QVBoxLayout>

#include "qtui.h"

NotificationsSettingsPage::NotificationsSettingsPage(QWidget* parent)
    : SettingsPage(tr("Interface"), tr("Notifications"), parent)
{
    auto* layout = new QVBoxLayout(this);
    foreach (AbstractNotificationBackend* backend, QtUi::notificationBackends()) {
        SettingsPage* cw = backend->createConfigWidget();
        if (cw) {
            cw->setParent(this);
            _configWidgets.append(cw);
            layout->addWidget(cw);
            connect(cw, &SettingsPage::changed, this, &NotificationsSettingsPage::widgetHasChanged);
            _hasDefaults |= cw->hasDefaults();
        }
    }
    layout->addStretch(20);
    load();
}

bool NotificationsSettingsPage::hasDefaults() const
{
    return _hasDefaults;
}

void NotificationsSettingsPage::defaults()
{
    foreach (SettingsPage* cw, _configWidgets)
        cw->defaults();
    widgetHasChanged();
}

void NotificationsSettingsPage::load()
{
    foreach (SettingsPage* cw, _configWidgets)
        cw->load();
    setChangedState(false);
}

void NotificationsSettingsPage::save()
{
    foreach (SettingsPage* cw, _configWidgets)
        cw->save();
    setChangedState(false);
}

void NotificationsSettingsPage::widgetHasChanged()
{
    bool changed = false;
    foreach (SettingsPage* cw, _configWidgets) {
        if (cw->hasChanged()) {
            changed = true;
            break;
        }
    }
    if (changed != hasChanged())
        setChangedState(changed);
}
