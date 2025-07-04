// SPDX-FileCopyrightText: 2005-2025 Quassel Project <devel@quassel-irc.org>
// SPDX-License-Identifier: GPL-2.0-or-later

#include "dockmanagernotificationbackend.h"

#include <QCheckBox>
#include <QDBusReply>
#include <QHBoxLayout>

#include "client.h"
#include "clientbacklogmanager.h"
#include "clientsettings.h"
#include "coreconnection.h"
#include "util.h"

DockManagerNotificationBackend::DockManagerNotificationBackend(QObject* parent)
    : AbstractNotificationBackend(parent)
    , _bus(QDBusConnection::sessionBus())
{
    NotificationSettings notificationSettings;
    _enabled = notificationSettings.value("DockManager/Enabled", false).toBool();

    notificationSettings.notify("DockManager/Enabled", this, &DockManagerNotificationBackend::enabledChanged);

    _dock = new QDBusInterface("net.launchpad.DockManager", "/net/launchpad/DockManager", "net.launchpad.DockManager", _bus, this);
    if (_dock->isValid()) {
        _bus.connect("net.launchpad.DockManager",
                     "/net/launchpad/DockManager",
                     "net.launchpad.DockManager",
                     "ItemAdded",
                     this,
                     SLOT(itemAdded(QDBusObjectPath)));
    }
    else {
        // evil implementations (awn) use fd.o
        _dock = new QDBusInterface("org.freedesktop.DockManager", "/org/freedesktop/DockManager", "org.freedesktop.DockManager", _bus, this);
        if (_dock->isValid()) {
            _bus.connect("org.freedesktop.DockManager",
                         "/org/freedesktop/DockManager",
                         "org.freedesktop.DockManager",
                         "ItemAdded",
                         this,
                         SLOT(itemAdded(QDBusObjectPath)));
        }
        else {
            _available = _enabled = false;
            return;
        }
    }
    _available = true;

    itemAdded(QDBusObjectPath());

    connect(Client::coreConnection(),
            &CoreConnection::progressValueChanged,
            this,
            selectOverload<int>(&DockManagerNotificationBackend::updateProgress));
    connect(Client::coreConnection(), &CoreConnection::synchronized, this, &DockManagerNotificationBackend::synchronized);
}

void DockManagerNotificationBackend::itemAdded(QDBusObjectPath p)
{
    Q_UNUSED(p);

    if (_item)
        return;

    // stupid implementations (awn; kde?) use wrong casing of PID, but proper type
    QDBusReply<QList<QDBusObjectPath>> paths = _dock->call("GetItemsByPid", (int)QCoreApplication::applicationPid());
    if (!paths.isValid()) {
        // stupid implementations (i.e. docky) use uint, but proper casing
        paths = _dock->call("GetItemsByPID", (unsigned int)QCoreApplication::applicationPid());
        if (!paths.isValid()) {
            qDebug() << "DBus error:" << paths.error().message();
            return;
        }
    }
    if (paths.value().count() == 0) {  // no icon for this instance
        return;
    }

    QString path = paths.value()[0].path();  // no sense in using multiple icons for one instance
    _item = new QDBusInterface("org.freedesktop.DockManager", path, "org.freedesktop.DockItem", _bus, this);
}

void DockManagerNotificationBackend::updateProgress(int progress)
{
    if (!_enabled || !_item)
        return;

    CoreConnection* c = Client::instance()->coreConnection();
    int perc = 0;
    if (c->progressMaximum() == c->progressMinimum())
        perc = 0;
    else
        perc = (progress - c->progressMinimum()) * 100 / (c->progressMaximum() - c->progressMinimum());

    QHash<QString, QVariant> args;
    args["progress"] = perc;
    _item->call("UpdateDockItem", args);
}

void DockManagerNotificationBackend::updateProgress(int done, int total)
{
    if (!_enabled || !_item)
        return;

    int perc = 0;
    if (done == total) {
        disconnect(Client::backlogManager(), nullptr, this, nullptr);
        perc = -1;
    }
    else
        perc = (done * 100) / total;

    QHash<QString, QVariant> args;
    args["progress"] = perc;
    _item->call("UpdateDockItem", args);
}

void DockManagerNotificationBackend::synchronized()
{
    connect(Client::backlogManager(),
            &ClientBacklogManager::updateProgress,
            this,
            selectOverload<int, int>(&DockManagerNotificationBackend::updateProgress));
}

void DockManagerNotificationBackend::notify(const Notification& notification)
{
    if (!_enabled || !_item) {
        return;
    }
    if (notification.type != Highlight && notification.type != PrivMsg) {
        return;
    }

    QHash<QString, QVariant> args;
    args["attention"] = true;
    args["badge"] = QString::number(++_count);
    _item->call("UpdateDockItem", args);
}

void DockManagerNotificationBackend::close(uint notificationId)
{
    Q_UNUSED(notificationId);
    if (!_item)
        return;

    QHash<QString, QVariant> args;
    args["attention"] = false;
    args["badge"] = --_count == 0 ? QString() : QString::number(_count);
    _item->call("UpdateDockItem", args);
}

void DockManagerNotificationBackend::enabledChanged(const QVariant& v)
{
    _enabled = v.toBool();

    if (!_enabled && _item) {
        QHash<QString, QVariant> args;
        args["attention"] = false;
        args["badge"] = QString();
        _item->call("UpdateDockItem", args);
    }
}

SettingsPage* DockManagerNotificationBackend::createConfigWidget() const
{
    return new ConfigWidget(_available);
}

/***************************************************************************/

DockManagerNotificationBackend::ConfigWidget::ConfigWidget(bool enabled, QWidget* parent)
    : SettingsPage("Internal", "DockManagerNotification", parent)
{
    auto* layout = new QHBoxLayout(this);
    layout->addWidget(enabledBox = new QCheckBox(tr("Mark dockmanager entry"), this));
    enabledBox->setVisible(enabled);

    connect(enabledBox, &QAbstractButton::toggled, this, &ConfigWidget::widgetChanged);
}

void DockManagerNotificationBackend::ConfigWidget::widgetChanged()
{
    bool changed = enabled != enabledBox->isChecked();

    if (changed != hasChanged())
        setChangedState(changed);
}

bool DockManagerNotificationBackend::ConfigWidget::hasDefaults() const
{
    return true;
}

void DockManagerNotificationBackend::ConfigWidget::defaults()
{
    enabledBox->setChecked(false);
    widgetChanged();
}

void DockManagerNotificationBackend::ConfigWidget::load()
{
    NotificationSettings s;
    enabled = s.value("DockManager/Enabled", false).toBool();

    enabledBox->setChecked(enabled);
    setChangedState(false);
}

void DockManagerNotificationBackend::ConfigWidget::save()
{
    NotificationSettings s;
    s.setValue("DockManager/Enabled", enabledBox->isChecked());
    load();
}
