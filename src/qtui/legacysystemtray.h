// SPDX-FileCopyrightText: 2005-2025 Quassel Project <devel@quassel-irc.org>
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

#ifndef QT_NO_SYSTEMTRAYICON

#    include <QString>
#    include <QSystemTrayIcon>

#    include "systemtray.h"

class LegacySystemTray : public SystemTray
{
    Q_OBJECT

public:
    explicit LegacySystemTray(QWidget* parent);

    bool isSystemTrayAvailable() const override;

public slots:
    void showMessage(const QString& title,
                     const QString& message,
                     MessageIcon icon = Information,
                     int msTimeout = 10000,
                     uint notificationId = 0) override;
    void closeMessage(uint notificationId) override;

private slots:
    void onModeChanged(Mode mode);
    void onVisibilityChanged(bool isVisible);

    void onActivated(QSystemTrayIcon::ActivationReason);
    void onMessageClicked();

    void updateIcon();
    void updateToolTip();

private:
    uint _lastMessageId{0};

    QSystemTrayIcon* _trayIcon;
};

#endif /* QT_NO_SYSTEMTRAYICON */
