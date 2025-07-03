// SPDX-FileCopyrightText: 2005-2025 Quassel Project <devel@quassel-irc.org>
// SPDX-License-Identifier: GPL-2.0-or-later

#ifndef OSXNOTIFICATIONBACKEND_H
#define OSXNOTIFICATIONBACKEND_H

#include "abstractnotificationbackend.h"
#include "settingspage.h"

class QCheckBox;

class OSXNotificationBackend : public AbstractNotificationBackend
{
    Q_OBJECT

public:
    OSXNotificationBackend(QObject* parent = nullptr);
    virtual ~OSXNotificationBackend(); // Declare the destructor

    void notify(const Notification&) override;
    void close(uint notificationId) override;
    SettingsPage* createConfigWidget() const override;

private slots:
    void enabledChanged(const QVariant&);

private:
    class ConfigWidget;

    bool _enabled;
};

class OSXNotificationBackend::ConfigWidget : public SettingsPage
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
    QCheckBox* _enabledBox;
    bool _enabled;
};

#endif // OSXNOTIFICATIONBACKEND_H
