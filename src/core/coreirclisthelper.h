// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

#include <memory>

#include "coresession.h"
#include "irclisthelper.h"

class QBasicTimer;
class QTimerEvent;

class CoreIrcListHelper : public IrcListHelper
{
    Q_OBJECT

public:
    inline CoreIrcListHelper(CoreSession* coreSession)
        : IrcListHelper(coreSession)
        , _coreSession(coreSession){};

    inline CoreSession* coreSession() const { return _coreSession; }

    inline bool requestInProgress(const NetworkId& netId) const { return _channelLists.contains(netId); }

public slots:
    QVariantList requestChannelList(const NetworkId& netId, const QStringList& channelFilters) override;
    bool addChannel(const NetworkId& netId, const QString& channelName, quint32 userCount, const QString& topic);
    bool endOfChannelList(const NetworkId& netId);

protected:
    void timerEvent(QTimerEvent* event) override;

private:
    bool dispatchQuery(const NetworkId& netId, const QString& query);

private:
    CoreSession* _coreSession;

    QHash<NetworkId, QString> _queuedQuery;
    QHash<NetworkId, QList<ChannelDescription>> _channelLists;
    QHash<NetworkId, QVariantList> _finishedChannelLists;
    QHash<int, NetworkId> _queryTimeoutByTimerId;
    QHash<NetworkId, std::shared_ptr<QBasicTimer>> _queryTimeoutByNetId;
};
