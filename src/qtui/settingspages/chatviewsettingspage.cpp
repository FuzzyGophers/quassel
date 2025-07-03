// SPDX-FileCopyrightText: 2005-2025 Quassel Project <devel@quassel-irc.org>
// SPDX-License-Identifier: GPL-2.0-or-later

#include "chatviewsettingspage.h"

#include "chatviewsettings.h"
#include "client.h"
#include "qtui.h"
#include "qtuistyle.h"
#include "uistyle.h"

ChatViewSettingsPage::ChatViewSettingsPage(QWidget* parent)
    : SettingsPage(tr("Interface"), tr("Chat View"), parent)
{
    ui.setupUi(this);

#if !defined HAVE_WEBKIT && !defined HAVE_WEBENGINE
    ui.showWebPreview->hide();
    ui.showWebPreview->setEnabled(false);
#endif

    // Handle UI dependent on core feature flags here
    // FIXME remove with protocol v11
    if (!Client::isCoreFeatureEnabled(Quassel::Feature::SynchronizedMarkerLine)) {
        ui.autoMarkerLine->setEnabled(false);
        ui.autoMarkerLine->setChecked(true);
        ui.autoMarkerLine->setToolTip(tr("You need at least version 0.6 of Quassel Core to use this feature"));
    }
    if (!Client::isCoreFeatureEnabled(Quassel::Feature::SenderPrefixes)) {
        // Sender prefixes are not supported, disallow toggling
        ui.senderPrefixComboBox->setEnabled(false);
        // Split up the message to allow re-using translations:
        // [Original tool-tip]
        // [Bold 'does not support feature' message]
        // [Specific version needed and feature details]
        ui.senderPrefixComboBox->setToolTip(QString("<b>%2</b><br/>%3")
                                                .arg(tr("Your Quassel core does not support this feature"),
                                                     tr("You need a Quassel core v0.13.0 or newer in order to show sender "
                                                        "modes before nicknames.")));
    }
    initAutoWidgets();
    initSenderPrefixComboBox();
}

void ChatViewSettingsPage::initSenderPrefixComboBox()
{
    // Fill combobox with sender prefix modes
    // Do not change ComboBox ordering without also adjusting chatviewsettingspage.ui "defaultValue"
    // and UiStyle::SenderPrefixMode
    ui.senderPrefixComboBox->addItem(tr("No modes"), static_cast<int>(UiStyle::SenderPrefixMode::NoModes));
    ui.senderPrefixComboBox->addItem(tr("Highest mode"), static_cast<int>(UiStyle::SenderPrefixMode::HighestMode));
    ui.senderPrefixComboBox->addItem(tr("All modes"), static_cast<int>(UiStyle::SenderPrefixMode::AllModes));
}

void ChatViewSettingsPage::save()
{
    bool needsStyleReload = SettingsPage::hasChanged(ui.customChatViewFont) || SettingsPage::hasChanged(ui.chatViewFont);

    // Save the general settings
    SettingsPage::save();

    // Update the stylesheet if fonts are changed
    if (needsStyleReload) {
        QtUi::style()->generateSettingsQss();
        QtUi::style()->reload();
    }
}
