// SPDX-FileCopyrightText: 2005-2025 Quassel Project <devel@quassel-irc.org>
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

#ifdef HAVE_DBUS

#    include <QDBusError>
#    include <QHash>
#    include <QString>
#    include <QTemporaryDir>

#    include "notificationsclient.h"
#    include "statusnotifierwatcher.h"
#    include "systemtray.h"

#    ifdef QT_NO_SYSTEMTRAYICON
#        define StatusNotifierItemParent SystemTray
#    else
#        define StatusNotifierItemParent LegacySystemTray
#        include "legacysystemtray.h"
#    endif

class QDBusServiceWatcher;

class StatusNotifierItemDBus;

class StatusNotifierItem : public StatusNotifierItemParent
{
    Q_OBJECT

public:
    explicit StatusNotifierItem(QWidget* parent);

    bool isSystemTrayAvailable() const override;

public slots:
    void showMessage(const QString& title,
                     const QString& message,
                     MessageIcon icon = Information,
                     int msTimeout = 10000,
                     uint notificationId = 0) override;
    void closeMessage(uint notificationId) override;

protected:
    QString title() const;
    QString iconName() const;
    QString attentionIconName() const;
    QString toolTipIconName() const;
    QString iconThemePath() const;
    QString menuObjectPath() const;

    bool eventFilter(QObject* watched, QEvent* event) override;

private slots:
    void activated(const QPoint& pos);
    void serviceChange(const QString& name, const QString& oldOwner, const QString& newOwner);
    void checkForRegisteredHosts();
    void onDBusError(const QDBusError& error);

    void notificationClosed(uint id, uint reason);
    void notificationInvoked(uint id, const QString& action);

    void refreshIcons();

    void onModeChanged(Mode mode);
    void onStateChanged(State state);
    void onVisibilityChanged(bool isVisible);

private:
    void registerToWatcher();

    QDBusServiceWatcher* _serviceWatcher{nullptr};
    StatusNotifierItemDBus* _statusNotifierItemDBus{nullptr};
    org::kde::StatusNotifierWatcher* _statusNotifierWatcher{nullptr};
    org::freedesktop::Notifications* _notificationsClient{nullptr};
    bool _notificationsClientSupportsMarkup{false};
    bool _notificationsClientSupportsActions{false};
    quint32 _lastNotificationsDBusId{0};
    QHash<uint, uint> _notificationsIdMap;  ///< Maps our own notification ID to the D-Bus one

    QString _iconThemePath;
    QString _menuObjectPath;

    QTemporaryDir _iconThemeDir;

    friend class StatusNotifierItemDBus;
};

#endif /* HAVE_DBUS */
