// SPDX-FileCopyrightText: 2005-2025 Quassel Project <devel@quassel-irc.org>
// SPDX-License-Identifier: GPL-2.0-or-later

#include "taskbarnotificationbackend.h"

#include <QApplication>
#include <QCheckBox>
#include <QHBoxLayout>
#include <QSpinBox>

#include "clientsettings.h"
#include "icon.h"
#include "mainwin.h"
#include "qtui.h"

TaskbarNotificationBackend::TaskbarNotificationBackend(QObject* parent)
    : AbstractNotificationBackend(parent)
{
    NotificationSettings notificationSettings;
    _enabled = notificationSettings.value("Taskbar/Enabled", true).toBool();
    _timeout = notificationSettings.value("Taskbar/Timeout", 0).toInt();

    notificationSettings.notify("Taskbar/Enabled", this, &TaskbarNotificationBackend::enabledChanged);
    notificationSettings.notify("Taskbar/Timeout", this, &TaskbarNotificationBackend::timeoutChanged);
}

void TaskbarNotificationBackend::notify(const Notification& notification)
{
    if (_enabled && (notification.type == Highlight || notification.type == PrivMsg)) {
        QApplication::alert(QtUi::mainWindow(), _timeout);
    }
}

void TaskbarNotificationBackend::close(uint notificationId)
{
    Q_UNUSED(notificationId);
}

void TaskbarNotificationBackend::enabledChanged(const QVariant& v)
{
    _enabled = v.toBool();
}

void TaskbarNotificationBackend::timeoutChanged(const QVariant& v)
{
    _timeout = v.toInt();
}

SettingsPage* TaskbarNotificationBackend::createConfigWidget() const
{
    return new ConfigWidget();
}

/***************************************************************************/

TaskbarNotificationBackend::ConfigWidget::ConfigWidget(QWidget* parent)
    : SettingsPage("Internal", "TaskbarNotification", parent)
{
    auto* layout = new QHBoxLayout(this);
#ifdef Q_OS_MAC
    layout->addWidget(enabledBox = new QCheckBox(tr("Activate dock entry, timeout:"), this));
#else
    layout->addWidget(enabledBox = new QCheckBox(tr("Mark taskbar entry, timeout:"), this));
#endif
    enabledBox->setIcon(icon::get("flag-blue"));
    enabledBox->setEnabled(true);

    timeoutBox = new QSpinBox(this);
    timeoutBox->setMinimum(0);
    timeoutBox->setMaximum(99);
    timeoutBox->setSpecialValueText(tr("Unlimited"));
    timeoutBox->setSuffix(tr(" seconds"));
    layout->addWidget(timeoutBox);
    layout->addStretch(20);

    connect(enabledBox, &QAbstractButton::toggled, this, &ConfigWidget::widgetChanged);
    connect(enabledBox, &QAbstractButton::toggled, timeoutBox, &QWidget::setEnabled);
    connect(timeoutBox, selectOverload<int>(&QSpinBox::valueChanged), this, &ConfigWidget::widgetChanged);
}

void TaskbarNotificationBackend::ConfigWidget::widgetChanged()
{
    bool changed = (enabled != enabledBox->isChecked() || timeout / 1000 != timeoutBox->value());
    if (changed != hasChanged())
        setChangedState(changed);
}

bool TaskbarNotificationBackend::ConfigWidget::hasDefaults() const
{
    return true;
}

void TaskbarNotificationBackend::ConfigWidget::defaults()
{
    enabledBox->setChecked(true);
    timeoutBox->setValue(0);
    widgetChanged();
}

void TaskbarNotificationBackend::ConfigWidget::load()
{
    NotificationSettings s;
    enabled = s.value("Taskbar/Enabled", true).toBool();
    timeout = s.value("Taskbar/Timeout", 0).toInt();

    enabledBox->setChecked(enabled);
    timeoutBox->setValue(timeout / 1000);

    setChangedState(false);
}

void TaskbarNotificationBackend::ConfigWidget::save()
{
    NotificationSettings s;
    s.setValue("Taskbar/Enabled", enabledBox->isChecked());
    s.setValue("Taskbar/Timeout", timeoutBox->value() * 1000);
    load();
}
