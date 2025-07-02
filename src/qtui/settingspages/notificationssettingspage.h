// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

#include <QHash>

#include "settingspage.h"

//! A settings page for configuring notifications
/** This class just vertically stacks the ConfigWidgets of the registered notification backends.
 *  \NOTE: When this is called, all backends need to be already registered. No dynamic changes
 *         are tracked or reacted to!
 */
class NotificationsSettingsPage : public SettingsPage
{
    Q_OBJECT

public:
    NotificationsSettingsPage(QWidget* parent = nullptr);

    bool hasDefaults() const override;

public slots:
    void save() final override;
    void load() final override;
    void defaults() final override;

private slots:
    void widgetHasChanged();

private:
    QList<SettingsPage*> _configWidgets;
    bool _hasDefaults{false};
};
