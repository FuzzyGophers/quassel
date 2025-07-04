// SPDX-FileCopyrightText: 2005-2025 Quassel Project <devel@quassel-irc.org>
// SPDX-License-Identifier: GPL-2.0-or-later

#ifndef KEYEVENT_H
#define KEYEVENT_H

#include <utility>

#include "ircevent.h"

class KeyEvent : public IrcEvent
{
public:
    enum ExchangeType
    {
        Init,
        Finish
    };

    explicit KeyEvent(EventManager::EventType type,
                      Network* network,
                      QHash<IrcTagKey, QString> tags,
                      QString prefix,
                      QString target,
                      ExchangeType exchangeType,
                      QByteArray key,
                      const QDateTime& timestamp = QDateTime())
        : IrcEvent(type, network, std::move(tags), std::move(prefix))
        , _exchangeType(exchangeType)
        , _target(std::move(target))
        , _key(std::move(key))
    {
        setTimestamp(timestamp);
    }

    inline ExchangeType exchangeType() const { return _exchangeType; }
    inline void setExchangeType(ExchangeType type) { _exchangeType = type; }

    inline QString target() const { return _target; }
    inline void setTarget(const QString& target) { _target = target; }

    inline QByteArray key() const { return _key; }
    inline void setKey(const QByteArray& key) { _key = key; }

    static Event* create(EventManager::EventType type, QVariantMap& map, Network* network);

protected:
    explicit KeyEvent(EventManager::EventType type, QVariantMap& map, Network* network);
    void toVariantMap(QVariantMap& map) const override;

    inline QString className() const override { return "KeyEvent"; }
    inline void debugInfo(QDebug& dbg) const override
    {
        NetworkEvent::debugInfo(dbg);
        dbg << ", prefix = " << qPrintable(prefix()) << ", target = " << qPrintable(target())
            << ", exchangetype = " << (exchangeType() == Init ? "init" : "finish") << ", key = " << key();
    }

private:
    ExchangeType _exchangeType;
    QString _target;
    QByteArray _key;
};

#endif
