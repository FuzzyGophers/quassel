// SPDX-FileCopyrightText: 2005-2025 Quassel Project <devel@quassel-irc.org>
// SPDX-License-Identifier: GPL-2.0-or-later

#include "networkconfig.h"

NetworkConfig::NetworkConfig(const QString& objectName, QObject* parent)
    : SyncableObject(objectName, parent)
{
}

void NetworkConfig::setPingTimeoutEnabled(bool enabled)
{
    if (_pingTimeoutEnabled == enabled)
        return;

    _pingTimeoutEnabled = enabled;
    SYNC(ARG(enabled))
    emit pingTimeoutEnabledSet(enabled);
}

void NetworkConfig::setPingInterval(int interval)
{
    if (_pingInterval == interval)
        return;

    _pingInterval = interval;
    SYNC(ARG(interval))
    emit pingIntervalSet(interval);
}

void NetworkConfig::setMaxPingCount(int count)
{
    if (_maxPingCount == count)
        return;

    _maxPingCount = count;
    SYNC(ARG(count))
}

void NetworkConfig::setAutoWhoEnabled(bool enabled)
{
    if (_autoWhoEnabled == enabled)
        return;

    _autoWhoEnabled = enabled;
    SYNC(ARG(enabled))
    emit autoWhoEnabledSet(enabled);
}

void NetworkConfig::setAutoWhoInterval(int interval)
{
    if (_autoWhoInterval == interval)
        return;

    _autoWhoInterval = interval;
    SYNC(ARG(interval))
    emit autoWhoIntervalSet(interval);
}

void NetworkConfig::setAutoWhoNickLimit(int nickLimit)
{
    if (_autoWhoNickLimit == nickLimit)
        return;

    _autoWhoNickLimit = nickLimit;
    SYNC(ARG(nickLimit))
}

void NetworkConfig::setAutoWhoDelay(int delay)
{
    if (_autoWhoDelay == delay)
        return;

    _autoWhoDelay = delay;
    SYNC(ARG(delay))
    emit autoWhoDelaySet(delay);
}

void NetworkConfig::setStandardCtcp(bool enabled)
{
    if (_standardCtcp == enabled)
        return;

    _standardCtcp = enabled;
    SYNC(ARG(enabled))
    emit standardCtcpSet(enabled);
}
