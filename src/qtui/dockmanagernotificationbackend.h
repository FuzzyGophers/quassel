// SPDX-FileCopyrightText: 2005-2025 Quassel Project <devel@quassel-irc.org>
// SPDX-License-Identifier: GPL-2.0-or-later

#ifndef DOCKMANAGERNOTIFICATIONBACKEND_H_
#define DOCKMANAGERNOTIFICATIONBACKEND_H_

#include <QDBusConnection>
#include <QDBusInterface>

#include "abstractnotificationbackend.h"
#include "settingspage.h"

class QCheckBox;

class DockManagerNotificationBackend : public AbstractNotificationBackend
{
    Q_OBJECT

public:
    DockManagerNotificationBackend(QObject* parent = nullptr);

    void notify(const Notification&) override;
    void close(uint notificationId) override;
    SettingsPage* createConfigWidget() const override;

private slots:
    void enabledChanged(const QVariant&);
    void updateProgress(int progress);
    void updateProgress(int done, int total);
    void itemAdded(QDBusObjectPath);
    void synchronized();

private:
    class ConfigWidget;
    bool _enabled;
    bool _available;
    QDBusConnection _bus;
    QDBusInterface* _dock{nullptr};
    QDBusInterface* _item{nullptr};
    int _count{0};
};

class DockManagerNotificationBackend::ConfigWidget : public SettingsPage
{
    Q_OBJECT

public:
    ConfigWidget(bool enabled, QWidget* parent = nullptr);

    void save() override;
    void load() override;
    bool hasDefaults() const override;
    void defaults() override;

private slots:
    void widgetChanged();

private:
    QCheckBox* enabledBox;
    bool enabled;
};

#endif
