// SPDX-FileCopyrightText: 2005-2025 Quassel Project <devel@quassel-irc.org>
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

#include <QPointer>

#include "abstractnotificationbackend.h"
#include "settingspage.h"
#include "systemtray.h"

class KNotification;
class KNotifyConfigWidget;

class KNotificationBackend : public AbstractNotificationBackend
{
    Q_OBJECT

public:
    KNotificationBackend(QObject* parent = nullptr);

    void notify(const Notification&) override;
    void close(uint notificationId) override;
    SettingsPage* createConfigWidget() const override;

private slots:
    void notificationActivated();
    void notificationActivated(SystemTray::ActivationReason);
    void notificationActivated(uint notificationId);

private:
    class ConfigWidget;

    void removeNotificationById(uint id);
    void updateToolTip();

    QList<QPair<uint, QPointer<KNotification>>> _notifications;
};

class KNotificationBackend::ConfigWidget : public SettingsPage
{
    Q_OBJECT

public:
    ConfigWidget(QWidget* parent = nullptr);

    void save() override;
    void load() override;

private slots:
    void widgetChanged(bool);

private:
    KNotifyConfigWidget* _widget;
};
