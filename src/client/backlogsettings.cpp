// SPDX-FileCopyrightText: 2005-2025 Quassel Project <devel@quassel-irc.org>
// SPDX-License-Identifier: GPL-2.0-or-later

#include "backlogsettings.h"

BacklogSettings::BacklogSettings()
    : ClientSettings("Backlog")
{}

int BacklogSettings::requesterType() const
{
    int _requesterType = localValue("RequesterType", BacklogRequester::AsNeeded).toInt();
    if (_requesterType == BacklogRequester::GlobalUnread) {
        // GlobalUnread is currently disabled; don't allow it to be used.  Reset to default instead.
        _requesterType = BacklogRequester::AsNeeded;
    }
    return _requesterType;
}

void BacklogSettings::setRequesterType(int requesterType)
{
    // This settings key is also used within ChatMonitorSettingsPage::ChatMonitorSettingsPage()
    setLocalValue("RequesterType", requesterType);
}

int BacklogSettings::dynamicBacklogAmount() const
{
    return localValue("DynamicBacklogAmount", 200).toInt();
}

void BacklogSettings::setDynamicBacklogAmount(int amount)
{
    return setLocalValue("DynamicBacklogAmount", amount);
}

bool BacklogSettings::ensureBacklogOnBufferShow() const
{
    // This settings key is also used within BufferWidget::BufferWidget()
    return localValue("EnsureBacklogOnBufferShow", true).toBool();
}

void BacklogSettings::setEnsureBacklogOnBufferShow(bool enabled)
{
    return setLocalValue("EnsureBacklogOnBufferShow", enabled);
}

int BacklogSettings::fixedBacklogAmount() const
{
    return localValue("FixedBacklogAmount", 500).toInt();
}

void BacklogSettings::setFixedBacklogAmount(int amount)
{
    return setLocalValue("FixedBacklogAmount", amount);
}

int BacklogSettings::globalUnreadBacklogLimit() const
{
    return localValue("GlobalUnreadBacklogLimit", 5000).toInt();
}

void BacklogSettings::setGlobalUnreadBacklogLimit(int limit)
{
    return setLocalValue("GlobalUnreadBacklogLimit", limit);
}

int BacklogSettings::globalUnreadBacklogAdditional() const
{
    return localValue("GlobalUnreadBacklogAdditional", 100).toInt();
}

void BacklogSettings::setGlobalUnreadBacklogAdditional(int additional)
{
    return setLocalValue("GlobalUnreadBacklogAdditional", additional);
}

int BacklogSettings::perBufferUnreadBacklogLimit() const
{
    return localValue("PerBufferUnreadBacklogLimit", 200).toInt();
}

void BacklogSettings::setPerBufferUnreadBacklogLimit(int limit)
{
    return setLocalValue("PerBufferUnreadBacklogLimit", limit);
}

int BacklogSettings::perBufferUnreadBacklogAdditional() const
{
    return localValue("PerBufferUnreadBacklogAdditional", 50).toInt();
}

void BacklogSettings::setPerBufferUnreadBacklogAdditional(int additional)
{
    return setLocalValue("PerBufferUnreadBacklogAdditional", additional);
}

int BacklogSettings::asNeededLegacyBacklogAmount() const
{
    // Mimic FixedBacklogAmount defaults.  This is only used on cores lacking
    // Feature::BufferActivitySync.
    return localValue("AsNeededLegacyBacklogAmount", 500).toInt();
}

void BacklogSettings::setAsNeededLegacyBacklogAmount(int amount)
{
    return setLocalValue("AsNeededLegacyBacklogAmount", amount);
}
