// SPDX-FileCopyrightText: 2005-2025 Quassel Project <devel@quassel-irc.org>
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

#include "abstractnotificationbackend.h"
#include "settingspage.h"

#include "ui_systrayanimationconfigwidget.h"

class QCheckBox;

class SystrayAnimationNotificationBackend : public AbstractNotificationBackend
{
    Q_OBJECT

public:
    SystrayAnimationNotificationBackend(QObject* parent = nullptr);

    void notify(const Notification&) override;
    void close(uint notificationId) override;
    SettingsPage* createConfigWidget() const override;

private slots:
    void alertChanged(const QVariant&);

private:
    bool _alert{false};
    class ConfigWidget;
};

class SystrayAnimationNotificationBackend::ConfigWidget : public SettingsPage
{
    Q_OBJECT

public:
    ConfigWidget(QWidget* parent = nullptr);
    QString settingsKey() const override;

private:
    QVariant loadAutoWidgetValue(const QString& widgetName) override;
    void saveAutoWidgetValue(const QString& widgetName, const QVariant& value) override;

private:
    Ui::SystrayAnimationConfigWidget ui;
};
