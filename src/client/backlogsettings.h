// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

#include "client-export.h"

#include "backlogrequester.h"
#include "clientsettings.h"

class CLIENT_EXPORT BacklogSettings : public ClientSettings
{
public:
    BacklogSettings();
    int requesterType() const;
    // Default to PerBufferUnread to help work around performance problems on connect when there's
    // many buffers that don't have much activity.
    void setRequesterType(int requesterType);

    int dynamicBacklogAmount() const;
    void setDynamicBacklogAmount(int amount);

    /**
     * Gets if a buffer should fetch backlog upon show to provide a scrollable amount of backlog
     *
     * @return True if showing a buffer without scrollbar visible fetches backlog, otherwise false
     */
    bool ensureBacklogOnBufferShow() const;
    /**
     * Sets if a buffer should fetch backlog upon show to provide a scrollable amount of backlog
     *
     * @param enabled True if showing a buffer without scrollbar fetches backlog, otherwise false
     */
    void setEnsureBacklogOnBufferShow(bool enabled);

    int fixedBacklogAmount() const;
    void setFixedBacklogAmount(int amount);

    int globalUnreadBacklogLimit() const;
    void setGlobalUnreadBacklogLimit(int limit);
    int globalUnreadBacklogAdditional() const;
    void setGlobalUnreadBacklogAdditional(int additional);

    int perBufferUnreadBacklogLimit() const;
    void setPerBufferUnreadBacklogLimit(int limit);
    int perBufferUnreadBacklogAdditional() const;
    void setPerBufferUnreadBacklogAdditional(int additional);

    /**
     * Get the initial amount of backlog fetched across all buffers for legacy cores that do not
     * support Quassel::Feature::BufferActivitySync
     *
     * @seealso Quassel::Feature::BufferActivitySync
     * @return The amount of backlog to fetch per buffer
     */
    int asNeededLegacyBacklogAmount() const;
    /**
     * Set the initial amount of backlog fetched across all buffers for legacy cores that do not
     * support Quassel::Feature::BufferActivitySync
     *
     * @seealso BacklogSettings::asNeededLegacyBacklogAmount()
     * @param amount The amount of backlog to fetch per buffer
     */
    void setAsNeededLegacyBacklogAmount(int amount);
};
