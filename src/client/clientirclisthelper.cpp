// SPDX-FileCopyrightText: 2005-2025 Quassel Project <devel@quassel-irc.org>
// SPDX-License-Identifier: GPL-2.0-or-later

#include "clientirclisthelper.h"

#include <QStringList>

#include "client.h"
#include "irclistmodel.h"

QVariantList ClientIrcListHelper::requestChannelList(const NetworkId& netId, const QStringList& channelFilters)
{
    _netId = netId;
    return IrcListHelper::requestChannelList(netId, channelFilters);
}

void ClientIrcListHelper::receiveChannelList(const NetworkId& netId, const QStringList& channelFilters, const QVariantList& channels)
{
    QVariantList::const_iterator iter = channels.constBegin();
    QVariantList::const_iterator iterEnd = channels.constEnd();

    QList<ChannelDescription> channelList;
    while (iter != iterEnd) {
        QVariantList channelVar = iter->toList();
        ChannelDescription channelDescription(channelVar[0].toString(), channelVar[1].toUInt(), channelVar[2].toString());
        channelList << channelDescription;
        ++iter;
    }

    emit channelListReceived(netId, channelFilters, channelList);
}

void ClientIrcListHelper::reportFinishedList(const NetworkId& netId)
{
    if (_netId == netId) {
        requestChannelList(netId, QStringList());
        emit finishedListReported(netId);
    }
}
