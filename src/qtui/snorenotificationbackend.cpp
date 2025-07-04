// SPDX-FileCopyrightText: 2005-2025 Quassel Project <devel@quassel-irc.org>
// SPDX-License-Identifier: GPL-2.0-or-later

#include "snorenotificationbackend.h"

#include <iostream>

#include <QMetaObject>
#include <QtGlobal>
#include <QtGui>

#include <libsnore/notification/notification.h>
#include <libsnore/snore.h>

#include "client.h"
#include "icon.h"
#include "networkmodel.h"
#include "qtui.h"
#include "systraynotificationbackend.h"

SnoreNotificationBackend::SnoreNotificationBackend(QObject* parent)
    : AbstractNotificationBackend(parent)
    , m_icon(icon::get("quassel"))
{
    Snore::SnoreCore::instance().loadPlugins(
#ifndef HAVE_KDE
        Snore::SnorePlugin::Backend |
#endif
        Snore::SnorePlugin::SecondaryBackend | Snore::SnorePlugin::Settings);
    m_application = Snore::Application("Quassel", m_icon);
    m_application.hints().setValue("windows-app-id", "QuasselProject.QuasselIRC");
    m_application.hints().setValue("pushover-token", "arNtsi983QSZUqU3KAZrFLKHGFPkdL");

    connect(&Snore::SnoreCore::instance(), &Snore::SnoreCore::actionInvoked, this, &SnoreNotificationBackend::actionInvoked);

    m_alert = Snore::Alert(tr("Private Message"), m_icon);
    m_application.addAlert(m_alert);
    Snore::SnoreCore::instance().setDefaultApplication(m_application);

    NotificationSettings notificationSettings;
    bool enabled = notificationSettings.value("Snore/Enabled", false).toBool();
    setTraybackend(enabled);
    notificationSettings.notify("Snore/Enabled", this, &SnoreNotificationBackend::setTraybackend);
}

SnoreNotificationBackend::~SnoreNotificationBackend()
{
    Snore::SnoreCore::instance().deregisterApplication(m_application);
}

void SnoreNotificationBackend::notify(const Notification& n)
{
#ifndef HAVE_KDE
    if (m_systrayBackend != nullptr) {
        return;
    }
#endif
    QString title = QString("%1 - %2").arg(Client::networkModel()->networkName(n.bufferId), Client::networkModel()->bufferName(n.bufferId));
    QString message = QString("<%1> %2").arg(n.sender, n.message);
    Snore::Notification noti(m_application, m_alert, title, message, m_icon);
    noti.hints().setValue("QUASSEL_ID", n.notificationId);
    m_notificationIds.insert(n.notificationId, noti.id());
    Snore::SnoreCore::instance().broadcastNotification(noti);
}

void SnoreNotificationBackend::close(uint notificationId)
{
#ifndef HAVE_KDE
    if (m_systrayBackend != nullptr) {
        return;
    }
#endif
    Snore::Notification n = Snore::SnoreCore::instance().getActiveNotificationByID(m_notificationIds.take(notificationId));
    if (n.isValid()) {  // Don't close the notification if it no longer exists.
        Snore::SnoreCore::instance().requestCloseNotification(n, Snore::Notification::Closed);
    }
}

void SnoreNotificationBackend::actionInvoked(Snore::Notification n)
{
    emit activated(n.hints().value("QUASSEL_ID").toUInt());
}

SettingsPage* SnoreNotificationBackend::createConfigWidget() const
{
    return new ConfigWidget();
}

void SnoreNotificationBackend::setTraybackend(const QVariant& b)
{
#ifndef HAVE_KDE
    if (!b.toBool()) {
        if (m_systrayBackend == nullptr) {
            m_systrayBackend = new SystrayNotificationBackend(this);
            QtUi::registerNotificationBackend(m_systrayBackend);
        }
    }
    else {
        if (m_systrayBackend != nullptr) {
            QtUi::unregisterNotificationBackend(m_systrayBackend);
            m_systrayBackend->deleteLater();
            m_systrayBackend = nullptr;
        }
    }
#endif
    if (b.toBool()) {
        if (!Snore::SnoreCore::instance().aplications().contains(m_application.name())) {
            Snore::SnoreCore::instance().registerApplication(m_application);
        }
    }
    else {
        if (Snore::SnoreCore::instance().aplications().contains(m_application.name())) {
            Snore::SnoreCore::instance().deregisterApplication(m_application);
        }
    }
}

/***************************************************************************/

SnoreNotificationBackend::ConfigWidget::ConfigWidget(QWidget* parent)
    : SettingsPage("Internal", "SnoreNotification", parent)
{
    ui.setupUi(this);
    connect(ui.useSnoreCheckBox, &QCheckBox::toggled, this, &ConfigWidget::useSnoreChanged);
}

bool SnoreNotificationBackend::ConfigWidget::hasDefaults() const
{
    return true;
}

void SnoreNotificationBackend::ConfigWidget::defaults()
{
    useSnoreChanged(false);
    ui.widget->reset();
}

void SnoreNotificationBackend::ConfigWidget::load()
{
    NotificationSettings s;
    bool enabled = s.value("Snore/Enabled", false).toBool();
    ui.useSnoreCheckBox->setChecked(enabled);
    ui.widget->setEnabled(enabled);
    setChangedState(false);
    QMetaObject::invokeMethod(this, "changed", Qt::QueuedConnection);  // hack to make apply and accept button work for snore settings widget
}

void SnoreNotificationBackend::ConfigWidget::save()
{
    NotificationSettings s;
    s.setValue("Snore/Enabled", ui.useSnoreCheckBox->isChecked());
    ui.widget->accept();
    load();
}

void SnoreNotificationBackend::ConfigWidget::useSnoreChanged(bool b)
{
    ui.useSnoreCheckBox->setChecked(b);
    ui.widget->setEnabled(b);
    setChangedState(true);
}
