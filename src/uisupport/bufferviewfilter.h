// SPDX-FileCopyrightText: 2005-2025 Quassel Project <devel@quassel-irc.org>
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

#include "uisupport-export.h"

#include <QAction>
#include <QDropEvent>
#include <QFlags>
#include <QPointer>
#include <QSet>
#include <QSortFilterProxyModel>

#include "bufferviewconfig.h"
#include "types.h"

/*****************************************
 * Buffer View Filter
 *****************************************/
class UISUPPORT_EXPORT BufferViewFilter : public QSortFilterProxyModel
{
    Q_OBJECT

public:
    enum Mode
    {
        NoActive = 0x01,
        NoInactive = 0x02,
        SomeNets = 0x04,
        AllNets = 0x08,
        NoChannels = 0x10,
        NoQueries = 0x20,
        NoServers = 0x40,
        FullCustom = 0x80
    };
    Q_DECLARE_FLAGS(Modes, Mode)

    BufferViewFilter(QAbstractItemModel* model, BufferViewConfig* config = nullptr);

    Qt::ItemFlags flags(const QModelIndex& index) const override;
    bool dropMimeData(const QMimeData* data, Qt::DropAction action, int row, int column, const QModelIndex& parent) override;

    QVariant data(const QModelIndex& index, int role) const override;
    QVariant checkedState(const QModelIndex& index) const;

    bool setData(const QModelIndex& index, const QVariant& value, int role = Qt::EditRole) override;
    bool setCheckedState(const QModelIndex& index, Qt::CheckState state);

    void setConfig(BufferViewConfig* config);
    inline BufferViewConfig* config() const { return _config; }

    void sort(int column, Qt::SortOrder order = Qt::AscendingOrder) override;

    QList<QAction*> actions(const QModelIndex& index);

    void setFilterString(const QString string);

protected:
    bool filterAcceptsRow(int source_row, const QModelIndex& source_parent) const override;
    bool lessThan(const QModelIndex& source_left, const QModelIndex& source_right) const override;
    bool bufferLessThan(const QModelIndex& source_left, const QModelIndex& source_right) const;
    bool networkLessThan(const QModelIndex& source_left, const QModelIndex& source_right) const;

signals:
    void configChanged();

private slots:
    void configInitialized();
    void enableEditMode(bool enable);
    void showServerQueriesChanged();

private:
    QPointer<BufferViewConfig> _config;
    Qt::SortOrder _sortOrder;

    bool _showServerQueries;
    bool _editMode;
    QAction _enableEditMode;
    QSet<BufferId> _toAdd;
    QSet<BufferId> _toTempRemove;
    QSet<BufferId> _toRemove;
    QString _filterString;

    bool filterAcceptBuffer(const QModelIndex&) const;
    bool filterAcceptNetwork(const QModelIndex&) const;
    void addBuffer(const BufferId& bufferId) const;
    void addBuffers(const QList<BufferId>& bufferIds) const;
    static bool bufferIdLessThan(const BufferId&, const BufferId&);
};

Q_DECLARE_OPERATORS_FOR_FLAGS(BufferViewFilter::Modes)
