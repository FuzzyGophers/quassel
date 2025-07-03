// SPDX-FileCopyrightText: 2005-2025 Quassel Project <devel@quassel-irc.org>
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

#include "common-export.h"

#include <QDateTime>
#include <QDebug>

#include "eventmanager.h"

class Network;

class COMMON_EXPORT Event
{
public:
    explicit Event(EventManager::EventType type = EventManager::Invalid);
    virtual ~Event() = default;

    inline EventManager::EventType type() const { return _type; }

    inline void setFlag(EventManager::EventFlag flag) { _flags |= flag; }
    inline void setFlags(EventManager::EventFlags flags) { _flags = flags; }
    inline bool testFlag(EventManager::EventFlag flag) { return _flags.testFlag(flag); }
    inline EventManager::EventFlags flags() const { return _flags; }

    inline bool isValid() const { return _valid; }
    inline void stop() { setFlag(EventManager::Stopped); }
    inline bool isStopped() { return _flags.testFlag(EventManager::Stopped); }

    inline void setTimestamp(const QDateTime& time) { _timestamp = time; }
    inline QDateTime timestamp() const { return _timestamp; }

    // inline void setData(const QVariant &data) { _data = data; }
    // inline QVariant data() const { return _data; }

    // call EventManager::createEvent(map) instead!
    static Event* fromVariantMap(QVariantMap& map, Network* network);
    QVariantMap toVariantMap() const;

protected:
    virtual inline QString className() const { return "Event"; }
    virtual inline void debugInfo(QDebug& dbg) const { Q_UNUSED(dbg); }

    explicit Event(EventManager::EventType type, QVariantMap& map);

    // must only use primitive types: string, int, double, list, hash
    // we want to convert this to JSON in the future!
    virtual void toVariantMap(QVariantMap& map) const;

    inline void setValid(bool valid) { _valid = valid; }

private:
    EventManager::EventType _type;
    EventManager::EventFlags _flags;
    QDateTime _timestamp;
    bool _valid{true};

    friend COMMON_EXPORT QDebug operator<<(QDebug dbg, Event* e);
};

COMMON_EXPORT QDebug operator<<(QDebug dbg, Event* e);
