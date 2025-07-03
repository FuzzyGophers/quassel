// SPDX-FileCopyrightText: 2005-2025 Quassel Project <devel@quassel-irc.org>
// SPDX-License-Identifier: GPL-2.0-or-later

#include "buffersettings.h"

BufferSettings::BufferSettings(BufferId bufferId)
    : ClientSettings(QString("Buffer/%1").arg(bufferId.toInt()))
{}

BufferSettings::BufferSettings(const QString& idString)
    : ClientSettings(QString("Buffer/%1").arg(idString))
{}

void BufferSettings::setValue(const QString& key, const QVariant& data)
{
    setLocalValue(key, data);
}

QVariant BufferSettings::value(const QString& key, const QVariant& def) const
{
    return localValue(key, def);
}

void BufferSettings::filterMessage(Message::Type msgType, bool filter)
{
    if (!hasFilter())
        setLocalValue("hasMessageTypeFilter", true);
    if (filter)
        setLocalValue("MessageTypeFilter", localValue("MessageTypeFilter", 0).toInt() | msgType);
    else
        setLocalValue("MessageTypeFilter", localValue("MessageTypeFilter", 0).toInt() & ~msgType);
}

bool BufferSettings::hasFilter() const
{
    return localValue("hasMessageTypeFilter", false).toBool();
}

int BufferSettings::messageFilter() const
{
    return localValue("MessageTypeFilter", 0).toInt();
}

void BufferSettings::setMessageFilter(int filter)
{
    if (!hasFilter())
        setLocalValue("hasMessageTypeFilter", true);
    setLocalValue("MessageTypeFilter", filter);
}

void BufferSettings::removeFilter()
{
    setLocalValue("hasMessageTypeFilter", false);
    removeLocalKey("MessageTypeFilter");
}

bool BufferSettings::showUserStateIcons() const
{
    return localValue("ShowUserStateIcons", true).toBool();
}

void BufferSettings::enableUserStateIcons(bool enabled)
{
    setLocalValue("ShowUserStateIcons", enabled);
}

int BufferSettings::userNoticesTarget() const
{
    return localValue("UserNoticesTarget", RedirectTarget::DefaultBuffer | RedirectTarget::CurrentBuffer).toInt();
}

void BufferSettings::setUserNoticesTarget(int target)
{
    setLocalValue("UserNoticesTarget", target);
}

int BufferSettings::serverNoticesTarget() const
{
    return localValue("ServerNoticesTarget", RedirectTarget::StatusBuffer).toInt();
}

void BufferSettings::setServerNoticesTarget(int target)
{
    setLocalValue("ServerNoticesTarget", target);
}

int BufferSettings::errorMsgsTarget() const
{
    return localValue("ErrorMsgsTarget", RedirectTarget::DefaultBuffer).toInt();
}

void BufferSettings::setErrorMsgsTarget(int target)
{
    setLocalValue("ErrorMsgsTarget", target);
}
