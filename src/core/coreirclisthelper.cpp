// SPDX-FileCopyrightText: 2005-2025 Quassel Project <devel@quassel-irc.org>
// SPDX-License-Identifier: GPL-2.0-or-later

#include "coreirclisthelper.h"

#include "corenetwork.h"
#include "coreuserinputhandler.h"

constexpr auto kTimeoutMs = 5000;

QVariantList CoreIrcListHelper::requestChannelList(const NetworkId& netId, const QStringList& channelFilters)
{
    if (_finishedChannelLists.contains(netId))
        return _finishedChannelLists.take(netId);

    if (_channelLists.contains(netId)) {
        _queuedQuery[netId] = channelFilters.join(",");
    }
    else {
        dispatchQuery(netId, channelFilters.join(","));
    }
    return QVariantList();
}

bool CoreIrcListHelper::addChannel(const NetworkId& netId, const QString& channelName, quint32 userCount, const QString& topic)
{
    if (!_channelLists.contains(netId))
        return false;

    _channelLists[netId] << ChannelDescription(channelName, userCount, topic);
    if (_queryTimeoutByNetId.contains(netId))
        _queryTimeoutByNetId[netId]->start(kTimeoutMs, this);

    return true;
}

bool CoreIrcListHelper::dispatchQuery(const NetworkId& netId, const QString& query)
{
    CoreNetwork* network = coreSession()->network(netId);
    if (network) {
        _channelLists[netId] = QList<ChannelDescription>();
        network->userInputHandler()->handleList(BufferInfo(), query);

        auto timer = std::make_shared<QBasicTimer>();
        timer->start(kTimeoutMs, this);
        _queryTimeoutByNetId[netId] = timer;
        _queryTimeoutByTimerId[timer->timerId()] = netId;

        return true;
    }
    else {
        return false;
    }
}

bool CoreIrcListHelper::endOfChannelList(const NetworkId& netId)
{
    if (_queryTimeoutByNetId.contains(netId)) {
        // If we received an actual RPL_LISTEND, remove the timer
        int timerId = _queryTimeoutByNetId.take(netId)->timerId();
        _queryTimeoutByTimerId.remove(timerId);
    }

    if (_queuedQuery.contains(netId)) {
        // we're no longer interested in the current data. drop it and issue a new request.
        return dispatchQuery(netId, _queuedQuery.take(netId));
    }
    else if (_channelLists.contains(netId)) {
        QVariantList channelList;
        foreach (ChannelDescription channel, _channelLists[netId]) {
            QVariantList channelVariant;
            channelVariant << channel.channelName << channel.userCount << channel.topic;
            channelList << QVariant::fromValue<QVariant>(channelVariant);
        }
        _finishedChannelLists[netId] = channelList;
        _channelLists.remove(netId);
        reportFinishedList(netId);
        return true;
    }
    else {
        return false;
    }
}

void CoreIrcListHelper::timerEvent(QTimerEvent* event)
{
    if (!_queryTimeoutByTimerId.contains(event->timerId())) {
        IrcListHelper::timerEvent(event);
        return;
    }

    NetworkId netId = _queryTimeoutByTimerId.take(event->timerId());
    _queryTimeoutByNetId.remove(netId);

    event->accept();
    endOfChannelList(netId);
}
