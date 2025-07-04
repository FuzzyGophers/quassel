// SPDX-FileCopyrightText: 2005-2025 Quassel Project <devel@quassel-irc.org>
// SPDX-License-Identifier: GPL-2.0-or-later

#include "systraynotificationbackend.h"

#include <QApplication>
#include <QCheckBox>
#include <QGroupBox>
#include <QHBoxLayout>

#include "client.h"
#include "clientsettings.h"
#include "icon.h"
#include "mainwin.h"
#include "networkmodel.h"
#include "qtui.h"
#include "systemtray.h"

SystrayNotificationBackend::SystrayNotificationBackend(QObject* parent)
    : AbstractNotificationBackend(parent)
{
    NotificationSettings notificationSettings;
    notificationSettings.initAndNotify("Systray/ShowBubble", this, &SystrayNotificationBackend::showBubbleChanged, true);

    connect(QtUi::mainWindow()->systemTray(),
            &SystemTray::messageClicked,
            this,
            selectOverload<uint>(&SystrayNotificationBackend::onNotificationActivated));
    connect(QtUi::mainWindow()->systemTray(),
            &SystemTray::activated,
            this,
            selectOverload<SystemTray::ActivationReason>(&SystrayNotificationBackend::onNotificationActivated));

    QApplication::instance()->installEventFilter(this);

    updateToolTip();
}

void SystrayNotificationBackend::notify(const Notification& n)
{
    if (n.type != Highlight && n.type != PrivMsg)
        return;

    _notifications.append(n);
    if (_showBubble) {
        QString title = Client::networkModel()->networkName(n.bufferId) + " - " + Client::networkModel()->bufferName(n.bufferId);
        QString message = QString("<%1> %2").arg(n.sender, n.message);
        QtUi::mainWindow()->systemTray()->showMessage(title, message, SystemTray::Information, 10000, n.notificationId);
    }

    updateToolTip();
}

void SystrayNotificationBackend::close(uint notificationId)
{
    QList<Notification>::iterator i = _notifications.begin();
    while (i != _notifications.end()) {
        if (i->notificationId == notificationId)
            i = _notifications.erase(i);
        else
            ++i;
    }

    QtUi::mainWindow()->systemTray()->closeMessage(notificationId);

    updateToolTip();
}

void SystrayNotificationBackend::onNotificationActivated(uint notificationId)
{
    if (!_blockActivation) {
        QList<Notification>::iterator i = _notifications.begin();
        while (i != _notifications.end()) {
            if (i->notificationId == notificationId) {
                if (QtUi::mainWindow()->systemTray()->mode() == SystemTray::Legacy)
                    _blockActivation = true;  // prevent double activation because both tray icon and bubble might send a signal
                emit activated(notificationId);
                break;
            }
            ++i;
        }
    }
}

void SystrayNotificationBackend::onNotificationActivated(SystemTray::ActivationReason reason)
{
    if (reason == SystemTray::Trigger) {
        if (_notifications.count()) {
            onNotificationActivated(_notifications.last().notificationId);
        }
        else {
            GraphicalUi::toggleMainWidget();
        }
    }
}

// moving the mouse or releasing the button means that we're not dealing with a double activation
bool SystrayNotificationBackend::eventFilter(QObject* obj, QEvent* event)
{
    if (event->type() == QEvent::MouseMove || event->type() == QEvent::MouseButtonRelease) {
        _blockActivation = false;
    }
    return AbstractNotificationBackend::eventFilter(obj, event);
}

void SystrayNotificationBackend::showBubbleChanged(const QVariant& v)
{
    _showBubble = v.toBool();
}

void SystrayNotificationBackend::updateToolTip()
{
    QtUi::mainWindow()->systemTray()->setToolTip("Quassel IRC",
                                                 _notifications.count() ? tr("%n pending highlight(s)", "", _notifications.count())
                                                                        : QString());
}

SettingsPage* SystrayNotificationBackend::createConfigWidget() const
{
    return new ConfigWidget();
}

/***************************************************************************/

SystrayNotificationBackend::ConfigWidget::ConfigWidget(QWidget* parent)
    : SettingsPage("Internal", "SystrayNotification", parent)
{
    _showBubbleBox = new QCheckBox(tr("Show a message in a popup"));
    _showBubbleBox->setIcon(icon::get("dialog-information"));
    connect(_showBubbleBox, &QAbstractButton::toggled, this, &ConfigWidget::widgetChanged);
    auto* layout = new QHBoxLayout(this);
    layout->addWidget(_showBubbleBox);
}

void SystrayNotificationBackend::ConfigWidget::widgetChanged()
{
    bool changed = (_showBubble != _showBubbleBox->isChecked());
    if (changed != hasChanged())
        setChangedState(changed);
}

bool SystrayNotificationBackend::ConfigWidget::hasDefaults() const
{
    return true;
}

void SystrayNotificationBackend::ConfigWidget::defaults()
{
    _showBubbleBox->setChecked(false);
    widgetChanged();
}

void SystrayNotificationBackend::ConfigWidget::load()
{
    NotificationSettings s;
    _showBubble = s.value("Systray/ShowBubble", false).toBool();
    _showBubbleBox->setChecked(_showBubble);
    setChangedState(false);
}

void SystrayNotificationBackend::ConfigWidget::save()
{
    NotificationSettings s;
    s.setValue("Systray/ShowBubble", _showBubbleBox->isChecked());
    load();
}
