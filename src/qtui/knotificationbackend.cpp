// SPDX-License-Identifier: GPL-2.0-or-later

#include "knotificationbackend.h"

#include <QTextDocument>
#include <QVBoxLayout>

#include <KNotifications/KNotification>
#include <KNotifyConfig/KNotifyConfigWidget>
#include <knotifications_version.h>

#include "client.h"
#include "icon.h"
#include "mainwin.h"
#include "networkmodel.h"
#include "qtui.h"
#include "util.h"

KNotificationBackend::KNotificationBackend(QObject* parent)
    : AbstractNotificationBackend(parent)
{
    connect(QtUi::mainWindow()->systemTray(),
            &SystemTray::activated,
            this,
            selectOverload<SystemTray::ActivationReason>(&KNotificationBackend::notificationActivated));

    updateToolTip();
}

void KNotificationBackend::notify(const Notification& n)
{
    QString type;
    switch (n.type) {
    case Highlight:
        type = "Highlight";
        break;
    case HighlightFocused:
        type = "HighlightFocused";
        break;
    case PrivMsg:
        type = "PrivMsg";
        break;
    case PrivMsgFocused:
        type = "PrivMsgFocused";
        break;
    }

    QString message = QString("<b>&lt;%1&gt;</b> %2").arg(n.sender, n.message.toHtmlEscaped());
    KNotification* notification = KNotification::event(type,
                                                       message,
                                                       QStringLiteral("dialog-information"),
                                                       QtUi::mainWindow(),
                                                       KNotification::RaiseWidgetOnActivation | KNotification::CloseWhenWidgetActivated
                                                           | KNotification::CloseOnTimeout);
    connect(notification,
            selectOverload<uint>(&KNotification::activated),
            this,
            selectOverload<>(&KNotificationBackend::notificationActivated));
#if KNOTIFICATIONS_VERSION >= QT_VERSION_CHECK(5,31,0)
    notification->setDefaultAction(tr("View"));
#else
    notification->setActions(QStringList{tr("View")});
#endif
    notification->setProperty("notificationId", n.notificationId);

    _notifications.append(qMakePair(n.notificationId, QPointer<KNotification>(notification)));

    updateToolTip();
}

void KNotificationBackend::removeNotificationById(uint notificationId)
{
    QList<QPair<uint, QPointer<KNotification>>>::iterator i = _notifications.begin();
    while (i != _notifications.end()) {
        if (i->first == notificationId) {
            if (i->second)
                i->second->close();
            i = _notifications.erase(i);
        }
        else
            ++i;
    }
    updateToolTip();
}

void KNotificationBackend::close(uint notificationId)
{
    removeNotificationById(notificationId);
    // if(!_notifications.count()) // FIXME make configurable
}

void KNotificationBackend::notificationActivated()
{
    uint id = 0;
    KNotification* n = qobject_cast<KNotification*>(sender());
    if (n)
        id = n->property("notificationId").toUInt();

    notificationActivated(id);
}

void KNotificationBackend::notificationActivated(SystemTray::ActivationReason reason)
{
    if (reason == SystemTray::Trigger) {
        if (_notifications.count())
            notificationActivated(_notifications.first().first);  // oldest one
        else
            GraphicalUi::toggleMainWidget();
    }
}

void KNotificationBackend::notificationActivated(uint notificationId)
{
    emit activated(notificationId);
}

void KNotificationBackend::updateToolTip()
{
    QtUi::mainWindow()->systemTray()->setToolTip("Quassel IRC",
                                                 _notifications.count() ? tr("%n pending highlight(s)", "", _notifications.count())
                                                                        : QString());
}

SettingsPage* KNotificationBackend::createConfigWidget() const
{
    return new ConfigWidget();
}

/***************************************************************************/

KNotificationBackend::ConfigWidget::ConfigWidget(QWidget* parent)
    : SettingsPage("Internal", "KNotification", parent)
{
    _widget = new KNotifyConfigWidget(this);
    _widget->setApplication("quassel");

    QVBoxLayout* layout = new QVBoxLayout(this);
    layout->addWidget(_widget);

    connect(_widget, &KNotifyConfigWidget::changed, this, &ConfigWidget::widgetChanged);
}

void KNotificationBackend::ConfigWidget::widgetChanged(bool changed)
{
    setChangedState(changed);
}

void KNotificationBackend::ConfigWidget::load()
{
    setChangedState(false);
}

void KNotificationBackend::ConfigWidget::save()
{
    _widget->save();
    load();
}
