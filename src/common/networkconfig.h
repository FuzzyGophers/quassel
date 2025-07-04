// SPDX-FileCopyrightText: 2005-2025 Quassel Project <devel@quassel-irc.org>
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

#include "common-export.h"

#include "syncableobject.h"

class COMMON_EXPORT NetworkConfig : public SyncableObject
{
    Q_OBJECT
    SYNCABLE_OBJECT

    Q_PROPERTY(bool pingTimeoutEnabled READ pingTimeoutEnabled WRITE setPingTimeoutEnabled)
    Q_PROPERTY(int pingInterval READ pingInterval WRITE setPingInterval)
    Q_PROPERTY(int maxPingCount READ maxPingCount WRITE setMaxPingCount)
    Q_PROPERTY(bool autoWhoEnabled READ autoWhoEnabled WRITE setAutoWhoEnabled)
    Q_PROPERTY(int autoWhoInterval READ autoWhoInterval WRITE setAutoWhoInterval)
    Q_PROPERTY(int autoWhoNickLimit READ autoWhoNickLimit WRITE setAutoWhoNickLimit)
    Q_PROPERTY(int autoWhoDelay READ autoWhoDelay WRITE setAutoWhoDelay)
    Q_PROPERTY(bool standardCtcp READ standardCtcp WRITE setStandardCtcp)

public:
    NetworkConfig(const QString& objectName = "GlobalNetworkConfig", QObject* parent = nullptr);

public slots:
    inline bool pingTimeoutEnabled() const { return _pingTimeoutEnabled; }
    void setPingTimeoutEnabled(bool);
    virtual inline void requestSetPingTimeoutEnabled(bool b) { REQUEST(ARG(b)) }

    inline int pingInterval() const { return _pingInterval; }
    void setPingInterval(int);
    virtual inline void requestSetPingInterval(int i) { REQUEST(ARG(i)) }

    inline int maxPingCount() const { return _maxPingCount; }
    void setMaxPingCount(int);
    virtual inline void requestSetMaxPingCount(int i) { REQUEST(ARG(i)) }

    inline bool autoWhoEnabled() const { return _autoWhoEnabled; }
    void setAutoWhoEnabled(bool);
    virtual inline void requestSetAutoWhoEnabled(bool b) { REQUEST(ARG(b)) }

    inline int autoWhoInterval() const { return _autoWhoInterval; }
    void setAutoWhoInterval(int);
    virtual inline void requestSetAutoWhoInterval(int i) { REQUEST(ARG(i)) }

    inline int autoWhoNickLimit() const { return _autoWhoNickLimit; }
    void setAutoWhoNickLimit(int);
    virtual inline void requestSetAutoWhoNickLimit(int i) { REQUEST(ARG(i)) }

    inline int autoWhoDelay() const { return _autoWhoDelay; }
    void setAutoWhoDelay(int);
    virtual inline void requestSetAutoWhoDelay(int i) { REQUEST(ARG(i)) }

    inline bool standardCtcp() const { return _standardCtcp; }
    void setStandardCtcp(bool);
    virtual inline void requestSetStandardCtcp(bool b){REQUEST(ARG(b))}

    signals : void pingTimeoutEnabledSet(bool);
    void pingIntervalSet(int);
    //   void maxPingCountSet(int);
    void autoWhoEnabledSet(bool);
    void autoWhoIntervalSet(int);
    //   void autoWhoNickLimitSet(int);
    void autoWhoDelaySet(int);
    void standardCtcpSet(bool);

    //   void setPingTimeoutEnabledRequested(bool);
    //   void setPingIntervalRequested(int);
    //   void setMaxPingCountRequested(int);
    //   void setAutoWhoEnabledRequested(bool);
    //   void setAutoWhoIntervalRequested(int);
    //   void setAutoWhoNickLimitRequested(int);
    //   void setAutoWhoDelayRequested(int);

private:
    bool _pingTimeoutEnabled{true};
    int _pingInterval{30};
    int _maxPingCount{6};

    bool _autoWhoEnabled{true};
    int _autoWhoInterval{90};
    int _autoWhoNickLimit{200};
    int _autoWhoDelay{5};

    bool _standardCtcp{false};
};
