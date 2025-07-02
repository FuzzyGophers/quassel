// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

#include "client-export.h"

#include "irclisthelper.h"

class CLIENT_EXPORT ClientIrcListHelper : public IrcListHelper
{
    Q_OBJECT

public:
    inline ClientIrcListHelper(QObject* object = nullptr)
        : IrcListHelper(object){};

public slots:
    QVariantList requestChannelList(const NetworkId& netId, const QStringList& channelFilters) override;
    void receiveChannelList(const NetworkId& netId, const QStringList& channelFilters, const QVariantList& channels) override;
    void reportFinishedList(const NetworkId& netId) override;
    inline void reportError(const QString& error) override { emit errorReported(error); }

signals:
    void channelListReceived(const NetworkId& netId,
                             const QStringList& channelFilters,
                             const QList<IrcListHelper::ChannelDescription>& channelList);
    void finishedListReported(const NetworkId& netId);
    void errorReported(const QString& error);

private:
    NetworkId _netId;
};
