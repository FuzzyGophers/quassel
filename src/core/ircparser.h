// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

#include <QTimeZone>

#include "coresession.h"
#include "irctag.h"

class Event;
class EventManager;
class IrcEvent;
class NetworkDataEvent;

class IrcParser : public QObject
{
    Q_OBJECT

public:
    explicit IrcParser(CoreSession* session);

    inline CoreSession* coreSession() const { return _coreSession; }
    inline EventManager* eventManager() const { return coreSession()->eventManager(); }

signals:
    void newEvent(Event*);

protected:
    Q_INVOKABLE void processNetworkIncoming(NetworkDataEvent* e);

    bool checkParamCount(const QString& cmd, const QList<QByteArray>& params, int minParams);

    // no-op if we don't have crypto support!
    QByteArray decrypt(Network* network, const QString& target, const QByteArray& message, bool isTopic = false);

private:
    CoreSession* _coreSession;

    bool _debugLogRawIrc;      ///< If true, include raw IRC socket messages in the debug log
    qint32 _debugLogRawNetId;  ///< Network ID for logging raw IRC socket messages, or -1 for all
    bool _debugLogParsedIrc;      ///< If true, include parsed IRC socket messages in the debug log
    qint32 _debugLogParsedNetId;  ///< Network ID for logging parsed IRC socket messages, or -1 for all
};
