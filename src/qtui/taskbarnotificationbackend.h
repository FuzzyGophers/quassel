// SPDX-FileCopyrightText: 2005-2025 Quassel Project <devel@quassel-irc.org>
// SPDX-License-Identifier: GPL-2.0-or-later

#ifndef TASKBARNOTIFICATIONBACKEND_H_
#define TASKBARNOTIFICATIONBACKEND_H_

#include "abstractnotificationbackend.h"
#include "settingspage.h"

class QCheckBox;
class QSpinBox;

class TaskbarNotificationBackend : public AbstractNotificationBackend
{
    Q_OBJECT

public:
    TaskbarNotificationBackend(QObject* parent = nullptr);

    void notify(const Notification&) override;
    void close(uint notificationId) override;
    SettingsPage* createConfigWidget() const override;

private slots:
    void enabledChanged(const QVariant&);
    void timeoutChanged(const QVariant&);

private:
    class ConfigWidget;

    bool _enabled;
    int _timeout;
};

class TaskbarNotificationBackend::ConfigWidget : public SettingsPage
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
    QCheckBox* enabledBox;
    QSpinBox* timeoutBox;

    bool enabled;
    int timeout;
};

#endif
