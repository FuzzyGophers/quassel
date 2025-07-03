// SPDX-FileCopyrightText: 2005-2025 Quassel Project <devel@quassel-irc.org>
// SPDX-License-Identifier: GPL-2.0-or-later

#include "client-export.h"

#include "clientsettings.h"
#include "message.h"
#include "types.h"

class CLIENT_EXPORT BufferSettings : public ClientSettings
{
public:
    enum RedirectTarget
    {
        DefaultBuffer = 0x01,
        StatusBuffer = 0x02,
        CurrentBuffer = 0x04
    };

    BufferSettings(const QString& idString = "__default__");
    BufferSettings(BufferId bufferId);

    void setValue(const QString& key, const QVariant& data);
    QVariant value(const QString& key, const QVariant& def = {}) const;

    // Message Filter (default and per view)
    bool hasFilter() const;
    int messageFilter() const;
    void setMessageFilter(int filter);
    void filterMessage(Message::Type msgType, bool filter);
    void removeFilter();

    // user state icons for query buffers (default)
    bool showUserStateIcons() const;
    void enableUserStateIcons(bool enabled);

    // redirection settings (default)
    int userNoticesTarget() const;
    void setUserNoticesTarget(int target);
    int serverNoticesTarget() const;
    void setServerNoticesTarget(int target);
    int errorMsgsTarget() const;
    void setErrorMsgsTarget(int target);
};
