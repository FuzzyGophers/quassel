// SPDX-License-Identifier: GPL-2.0-or-later

#include "inputwidgetsettingspage.h"

InputWidgetSettingsPage::InputWidgetSettingsPage(QWidget* parent)
    : SettingsPage(tr("Interface"), tr("Input Widget"), parent)
{
    ui.setupUi(this);
    initAutoWidgets();
}
