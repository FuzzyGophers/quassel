// SPDX-FileCopyrightText: 2005-2025 Quassel Project <devel@quassel-irc.org>
// SPDX-License-Identifier: GPL-2.0-or-later

#include "topicwidgetsettingspage.h"

TopicWidgetSettingsPage::TopicWidgetSettingsPage(QWidget* parent)
    : SettingsPage(tr("Interface"), tr("Topic Widget"), parent)
{
    ui.setupUi(this);

    initAutoWidgets();
}
