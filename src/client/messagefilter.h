// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

#include "client-export.h"

#include <set>

#include <QSortFilterProxyModel>

#include "bufferinfo.h"
#include "client.h"
#include "messagemodel.h"
#include "networkmodel.h"
#include "types.h"

class CLIENT_EXPORT MessageFilter : public QSortFilterProxyModel
{
    Q_OBJECT

protected:
    MessageFilter(QAbstractItemModel* source, QObject* parent = nullptr);

public:
    MessageFilter(MessageModel*, const QList<BufferId>& buffers = QList<BufferId>(), QObject* parent = nullptr);

    virtual QString idString() const;

    bool isSingleBufferFilter() const { return _validBuffers.count() == 1; }
    BufferId singleBufferId() const { return *(_validBuffers.constBegin()); }
    bool containsBuffer(const BufferId& id) const { return _validBuffers.contains(id); }
    QSet<BufferId> containedBuffers() const { return _validBuffers; }

    bool filterAcceptsRow(int sourceRow, const QModelIndex& sourceParent) const override;

public slots:
    void messageTypeFilterChanged();
    void messageRedirectionChanged();
    void requestBacklog();
    // redefined as public slot
    void invalidateFilter() { QSortFilterProxyModel::invalidateFilter(); }

protected:
    QString bufferName() const { return Client::networkModel()->bufferName(singleBufferId()); }
    BufferInfo::Type bufferType() const { return Client::networkModel()->bufferType(singleBufferId()); }
    NetworkId networkId() const { return Client::networkModel()->networkId(singleBufferId()); }

private:
    void init();

    QSet<BufferId> _validBuffers;
    std::set<qint64> _filteredQuitMsgTime;  ///< Timestamps (ms) of already forwarded quit messages
    int _messageTypeFilter;

    int _userNoticesTarget;
    int _serverNoticesTarget;
    int _errorMsgsTarget;
};
