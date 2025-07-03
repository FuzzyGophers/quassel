// SPDX-FileCopyrightText: 2005-2025 Quassel Project <devel@quassel-irc.org>
// SPDX-License-Identifier: GPL-2.0-or-later

#include "chatviewcolorsettingspage.h"

#include "client.h"
#include "colorbutton.h"
#include "qtui.h"
#include "qtuistyle.h"

ChatViewColorSettingsPage::ChatViewColorSettingsPage(QWidget* parent)
    : SettingsPage(tr("Interface"), tr("Chat View Colors"), parent)
{
    ui.setupUi(this);

    initAutoWidgets();
}

void ChatViewColorSettingsPage::save()
{
    // Save the general settings
    SettingsPage::save();
    // Update the stylesheet in case colors are changed
    QtUi::style()->generateSettingsQss();
    QtUi::style()->reload();
}
