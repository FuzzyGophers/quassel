// SPDX-FileCopyrightText: 2005-2025 Quassel Project <devel@quassel-irc.org>
// SPDX-License-Identifier: GPL-2.0-or-later

#ifndef CHATVIEWSETTINGSPAGE_H_
#define CHATVIEWSETTINGSPAGE_H_

#include "settingspage.h"

#include "ui_chatviewsettingspage.h"

class ColorButton;

class ChatViewSettingsPage : public SettingsPage
{
    Q_OBJECT

public:
    ChatViewSettingsPage(QWidget* parent = nullptr);

    inline bool hasDefaults() const override { return true; }

public slots:
    void save() override;

private:
    Ui::ChatViewSettingsPage ui;

    /**
     * Initialize the available options for sender prefixes
     */
    void initSenderPrefixComboBox();

    inline QString settingsKey() const override { return QString("QtUi/ChatView/__default__"); }
};

#endif
