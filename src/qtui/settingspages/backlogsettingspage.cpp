// SPDX-License-Identifier: GPL-2.0-or-later

#include "backlogsettingspage.h"

#include "backlogrequester.h"
#include "backlogsettings.h"
#include "qtui.h"
#include "widgethelpers.h"

BacklogSettingsPage::BacklogSettingsPage(QWidget* parent)
    : SettingsPage(tr("Interface"), tr("Backlog Fetching"), parent)
{
    ui.setupUi(this);
    initAutoWidgets();
    // not an auto widget, because we store index + 1

    // FIXME: global backlog requester disabled until issues ruled out
    ui.requesterType->removeItem(3);
    // If modifying ui.requesterType's item list, set to the index of "Globally unread messages"

    connectToWidgetChangedSignal(ui.requesterType, this, &BacklogSettingsPage::widgetHasChanged);
}

bool BacklogSettingsPage::hasDefaults() const
{
    return true;
}

void BacklogSettingsPage::defaults()
{
    ui.requesterType->setCurrentIndex(BacklogRequester::AsNeeded - 1);

    SettingsPage::defaults();
}

void BacklogSettingsPage::load()
{
    BacklogSettings backlogSettings;
    int index = backlogSettings.requesterType() - 1;
    ui.requesterType->setProperty("storedValue", index);
    ui.requesterType->setCurrentIndex(index);

    SettingsPage::load();
}

void BacklogSettingsPage::save()
{
    BacklogSettings backlogSettings;
    backlogSettings.setRequesterType(ui.requesterType->currentIndex() + 1);
    ui.requesterType->setProperty("storedValue", ui.requesterType->currentIndex());

    SettingsPage::save();
}

void BacklogSettingsPage::widgetHasChanged()
{
    setChangedState(ui.requesterType->currentIndex() != ui.requesterType->property("storedValue").toInt());
}
