// SPDX-License-Identifier: GPL-2.0-or-later

#include "topicwidgetsettingspage.h"

TopicWidgetSettingsPage::TopicWidgetSettingsPage(QWidget* parent)
    : SettingsPage(tr("Interface"), tr("Topic Widget"), parent)
{
    ui.setupUi(this);

    initAutoWidgets();
}
