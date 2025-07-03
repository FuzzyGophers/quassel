// SPDX-FileCopyrightText: 2005-2025 Quassel Project <devel@quassel-irc.org>
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

#include "settingspage.h"

#include "ui_chatviewcolorsettingspage.h"

class ColorButton;

class ChatViewColorSettingsPage : public SettingsPage
{
    Q_OBJECT

public:
    /**
     * Construct and initialize the ChatViewColorSettingsPage
     *
     * @param parent Parent QWidget object, such as the settings dialog
     */
    explicit ChatViewColorSettingsPage(QWidget* parent = nullptr);

    /**
     * Gets whether or not this settings page has defaults
     *
     * @return True if defaults available, otherwise false
     */
    inline bool hasDefaults() const override { return true; }

public slots:
    /**
     * Save and apply current settings
     */
    void save() override;

private:
    Ui::ChatViewColorSettingsPage ui;  /// Reference to the Qt settings page UI

    /**
     * Gets the settings path for configuration values
     *
     * @return QString pointing to settings group and key for configuration values
     */
    inline QString settingsKey() const override { return QString("QtUi/ChatView/__default__"); }
};
