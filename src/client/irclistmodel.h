// SPDX-FileCopyrightText: 2005-2025 Quassel Project <devel@quassel-irc.org>
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

#include "client-export.h"

#include <QAbstractItemModel>

#include "irclisthelper.h"

class CLIENT_EXPORT IrcListModel : public QAbstractItemModel
{
    Q_OBJECT

public:
    IrcListModel(QObject* parent = nullptr);

    QVariant data(const QModelIndex& index, int role) const override;
    Qt::ItemFlags flags(const QModelIndex& index) const override;

    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;

    QModelIndex index(int row, int column, const QModelIndex& parent = QModelIndex()) const override;

    inline QModelIndex parent(const QModelIndex&) const override { return {}; }

    inline int rowCount(const QModelIndex& parent = QModelIndex()) const override
    {
        Q_UNUSED(parent)
        return _channelList.count();
    }
    inline int columnCount(const QModelIndex& parent = QModelIndex()) const override
    {
        Q_UNUSED(parent)
        return 3;
    }

public slots:
    void setChannelList(const QList<IrcListHelper::ChannelDescription>& channelList = QList<IrcListHelper::ChannelDescription>());

private:
    QList<IrcListHelper::ChannelDescription> _channelList;
};
