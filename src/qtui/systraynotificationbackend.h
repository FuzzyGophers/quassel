// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

#include "abstractnotificationbackend.h"
#include "settingspage.h"
#include "systemtray.h"

class QCheckBox;

class SystrayNotificationBackend : public AbstractNotificationBackend
{
    Q_OBJECT

public:
    SystrayNotificationBackend(QObject* parent = nullptr);

    void notify(const Notification&) override;
    void close(uint notificationId) override;
    SettingsPage* createConfigWidget() const override;

protected:
    bool eventFilter(QObject* obj, QEvent* event) override;

private slots:
    void onNotificationActivated(uint notificationId);
    void onNotificationActivated(SystemTray::ActivationReason);

    void showBubbleChanged(const QVariant&);
    void updateToolTip();

private:
    class ConfigWidget;

    bool _showBubble;
    QList<Notification> _notifications;
    bool _blockActivation{false};
};

class SystrayNotificationBackend::ConfigWidget : public SettingsPage
{
    Q_OBJECT

public:
    ConfigWidget(QWidget* parent = nullptr);
    void save() override;
    void load() override;
    bool hasDefaults() const override;
    void defaults() override;

private slots:
    void widgetChanged();

private:
    QCheckBox* _showBubbleBox;
    bool _showBubble;
};
