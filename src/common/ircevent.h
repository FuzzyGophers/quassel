// SPDX-FileCopyrightText: 2005-2025 Quassel Project <devel@quassel-irc.org>
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

#include "common-export.h"

#include <utility>

#include "irctag.h"
#include "networkevent.h"
#include "util.h"

class COMMON_EXPORT IrcEvent : public NetworkEvent
{
public:
    explicit IrcEvent(
        EventManager::EventType type, Network* network, QHash<IrcTagKey, QString> tags, QString prefix, QStringList params = {})
        : NetworkEvent(type, network)
        , _tags(std::move(tags))
        , _prefix(std::move(prefix))
        , _params(std::move(params))
    {}

    inline QString prefix() const { return _prefix; }
    inline void setPrefix(const QString& prefix) { _prefix = prefix; }

    inline QHash<IrcTagKey, QString> tags() const { return _tags; }
    inline void setTags(const QHash<IrcTagKey, QString>& tags) { _tags = tags; }

    inline QString nick() const { return nickFromMask(prefix()); }

    inline QStringList params() const { return _params; }
    inline void setParams(const QStringList& params) { _params = params; }

    static Event* create(EventManager::EventType type, QVariantMap& map, Network* network);

protected:
    explicit IrcEvent(EventManager::EventType type, QVariantMap& map, Network* network);
    void toVariantMap(QVariantMap& map) const override;

    inline QString className() const override { return "IrcEvent"; }
    inline void debugInfo(QDebug& dbg) const override
    {
        NetworkEvent::debugInfo(dbg);
        dbg << ", prefix = " << qPrintable(prefix()) << ", params = " << params();
    }

private:
    QHash<IrcTagKey, QString> _tags;
    QString _prefix;
    QStringList _params;
};

class COMMON_EXPORT IrcEventNumeric : public IrcEvent
{
public:
    explicit IrcEventNumeric(uint number,
                             Network* network,
                             QHash<IrcTagKey, QString> tags,
                             QString prefix,
                             QString target,
                             QStringList params = {})
        : IrcEvent(EventManager::IrcEventNumeric, network, std::move(tags), std::move(prefix), std::move(params))
        , _number(number)
        , _target(std::move(target))
    {}

    inline uint number() const { return _number; }

    inline QString target() const { return _target; }
    inline void setTarget(const QString& target) { _target = target; }

protected:
    explicit IrcEventNumeric(EventManager::EventType type, QVariantMap& map, Network* network);
    void toVariantMap(QVariantMap& map) const override;

    inline QString className() const override { return "IrcEventNumeric"; }
    inline void debugInfo(QDebug& dbg) const override
    {
        dbg << ", num = " << number();
        NetworkEvent::debugInfo(dbg);
        dbg << ", target = " << qPrintable(target())
            << ", prefix = " << qPrintable(prefix())
            << ", params = " << params();
    }

private:
    uint _number;
    QString _target;

    friend class IrcEvent;
};

class COMMON_EXPORT IrcEventRawMessage : public IrcEvent
{
public:
    explicit IrcEventRawMessage(EventManager::EventType type,
                                Network* network,
                                QHash<IrcTagKey, QString> tags,
                                QByteArray rawMessage,
                                QString prefix,
                                QString target,
                                const QDateTime& timestamp = QDateTime())
        : IrcEvent(type, network, std::move(tags), std::move(prefix), QStringList() << target)
        , _rawMessage(std::move(rawMessage))
    {
        setTimestamp(timestamp);
    }

    inline QString target() const { return params().at(0); }
    inline void setTarget(const QString& target) { setParams(QStringList() << target); }

    inline QByteArray rawMessage() const { return _rawMessage; }
    inline void setRawMessage(const QByteArray& rawMessage) { _rawMessage = rawMessage; }

protected:
    explicit IrcEventRawMessage(EventManager::EventType type, QVariantMap& map, Network* network);
    void toVariantMap(QVariantMap& map) const override;

    inline QString className() const override { return "IrcEventRawMessage"; }
    inline void debugInfo(QDebug& dbg) const override
    {
        NetworkEvent::debugInfo(dbg);
        dbg << ", target = " << qPrintable(target())
            << ", prefix = " << qPrintable(prefix())
            << ", msg = " << rawMessage();
    }

private:
    QByteArray _rawMessage;

    friend class IrcEvent;
};
