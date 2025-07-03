// SPDX-FileCopyrightText: 2005-2025 Quassel Project <devel@quassel-irc.org>
// SPDX-License-Identifier: GPL-2.0-or-later

#ifndef SNORENOTIFICATIONBACKEND_H_
#define SNORENOTIFICATIONBACKEND_H_

#include <libsnore/notification/notification.h>
#include <libsnore/snore.h>

#include "abstractnotificationbackend.h"
#include "settingspage.h"

#include "ui_snorentificationconfigwidget.h"

class SystrayNotificationBackend;

class SnoreNotificationBackend : public AbstractNotificationBackend
{
    Q_OBJECT
public:
    SnoreNotificationBackend(QObject* parent);
    ~SnoreNotificationBackend();

    void notify(const Notification&);
    void close(uint notificationId);

    virtual SettingsPage* createConfigWidget() const;

public slots:
    void actionInvoked(Snore::Notification);

private slots:
    void setTraybackend(const QVariant& b);

private:
    class ConfigWidget;
#ifndef HAVE_KDE
    SystrayNotificationBackend* m_systrayBackend = nullptr;
#endif
    QHash<uint, uint> m_notificationIds;
    Snore::Icon m_icon;
    Snore::Application m_application;
    Snore::Alert m_alert;
};

class SnoreNotificationBackend::ConfigWidget : public SettingsPage
{
    Q_OBJECT

public:
    ConfigWidget(QWidget* parent = 0);

    bool hasDefaults() const;
    void defaults();
    void load();
    void save();
private slots:
    void useSnoreChanged(bool);

private:
    Ui::SnoreNotificationConfigWidget ui;
};

#endif
