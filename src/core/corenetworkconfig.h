// SPDX-FileCopyrightText: 2005-2025 Quassel Project <devel@quassel-irc.org>
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

#include "networkconfig.h"

class CoreSession;

class CoreNetworkConfig : public NetworkConfig
{
    Q_OBJECT

public:
    CoreNetworkConfig(const QString& objectName, CoreSession* parent);

    void save();

public slots:
    inline void requestSetPingTimeoutEnabled(bool enabled) override { setPingTimeoutEnabled(enabled); }
    inline void requestSetPingInterval(int interval) override { setPingInterval(interval); }
    inline void requestSetMaxPingCount(int count) override { setMaxPingCount(count); }
    inline void requestSetAutoWhoEnabled(bool enabled) override { setAutoWhoEnabled(enabled); }
    inline void requestSetAutoWhoInterval(int interval) override { setAutoWhoInterval(interval); }
    inline void requestSetAutoWhoNickLimit(int nickLimit) override { setAutoWhoNickLimit(nickLimit); }
    inline void requestSetAutoWhoDelay(int delay) override { setAutoWhoDelay(delay); }
    inline void requestSetStandardCtcp(bool enabled) override { setStandardCtcp(enabled); }
};
