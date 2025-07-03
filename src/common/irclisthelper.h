// SPDX-FileCopyrightText: 2005-2025 Quassel Project <devel@quassel-irc.org>
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

#include "common-export.h"

#include <utility>

#include "syncableobject.h"
#include "types.h"

/*
 * This is a little helper to display channel lists of a network.
 * The whole process is done in 3 steps:
 *  1.) the client requests to issue a LIST command with requestChannelList()
 *  2.) RPL_LIST fills on the core the list of available channels
 *      when RPL_LISTEND is received the clients will be informed, that they can pull the data
 *  3.) client pulls the data by calling requestChannelList again. receiving the data in receiveChannelList
 */
class COMMON_EXPORT IrcListHelper : public SyncableObject
{
    Q_OBJECT
    SYNCABLE_OBJECT

public:
    inline IrcListHelper(QObject* parent = nullptr)
        : SyncableObject(parent)
    {
        setInitialized();
    };

    struct ChannelDescription
    {
        QString channelName;
        quint32 userCount;
        QString topic;
        ChannelDescription(QString channelName_, quint32 userCount_, QString topic_)
            : channelName(std::move(channelName_))
            , userCount(userCount_)
            , topic(std::move(topic_)){};
    };

public slots:
    inline virtual QVariantList requestChannelList(const NetworkId& netId, const QStringList& channelFilters)
    {
        REQUEST(ARG(netId), ARG(channelFilters));
        return QVariantList();
    }
    inline virtual void receiveChannelList(const NetworkId&, const QStringList&, const QVariantList&){};
    inline virtual void reportFinishedList(const NetworkId& netId) { SYNC(ARG(netId)) }
    inline virtual void reportError(const QString& error) { SYNC(ARG(error)) }
};
