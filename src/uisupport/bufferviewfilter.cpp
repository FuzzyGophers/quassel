// SPDX-FileCopyrightText: 2005-2025 Quassel Project <devel@quassel-irc.org>
// SPDX-License-Identifier: GPL-2.0-or-later

#include "bufferviewfilter.h"

#include <QApplication>
#include <QBrush>
#include <QPalette>

#include "bufferinfo.h"
#include "buffermodel.h"
#include "buffersettings.h"
#include "client.h"
#include "clientbufferviewconfig.h"
#include "graphicalui.h"
#include "networkmodel.h"
#include "uistyle.h"
#include "util.h"

/*****************************************
 * The Filter for the Tree View
 *****************************************/
BufferViewFilter::BufferViewFilter(QAbstractItemModel* model, BufferViewConfig* config)
    : QSortFilterProxyModel(model)
    , _config(nullptr)
    , _sortOrder(Qt::AscendingOrder)
    , _showServerQueries(false)
    , _editMode(false)
    , _enableEditMode(tr("Show / Hide Chats"), this)
{
    setConfig(config);
    setSourceModel(model);

    setDynamicSortFilter(true);
    // Sort case-insensitively (primarily for network names; channels/nicks handled elsewhere)
    setSortCaseSensitivity(Qt::CaseInsensitive);

    _enableEditMode.setCheckable(true);
    _enableEditMode.setChecked(_editMode);
    connect(&_enableEditMode, &QAction::toggled, this, &BufferViewFilter::enableEditMode);

    BufferSettings defaultSettings;
    defaultSettings.notify("ServerNoticesTarget", this, &BufferViewFilter::showServerQueriesChanged);
    showServerQueriesChanged();
}

void BufferViewFilter::setConfig(BufferViewConfig* config)
{
    if (_config == config)
        return;

    if (_config) {
        disconnect(_config, nullptr, this, nullptr);
    }

    _config = config;

    if (!config) {
        invalidate();
        setObjectName("");
        return;
    }

    if (config->isInitialized()) {
        configInitialized();
    }
    else {
        // we use a queued connection here since manipulating the connection list of a sending object
        // doesn't seem to be such a good idea while executing a connected slots.
        connect(config, &SyncableObject::initDone, this, &BufferViewFilter::configInitialized, Qt::QueuedConnection);
        invalidate();
    }
}

void BufferViewFilter::configInitialized()
{
    if (!config())
        return;

    connect(config(), &BufferViewConfig::configChanged, this, &QSortFilterProxyModel::invalidate);

    disconnect(config(), &SyncableObject::initDone, this, &BufferViewFilter::configInitialized);

    setObjectName(config()->bufferViewName());

    invalidate();
    emit configChanged();
}

void BufferViewFilter::showServerQueriesChanged()
{
    BufferSettings bufferSettings;

    bool showQueries = (bufferSettings.serverNoticesTarget() & BufferSettings::DefaultBuffer);
    if (_showServerQueries != showQueries) {
        _showServerQueries = showQueries;
        invalidate();
    }
}

QList<QAction*> BufferViewFilter::actions(const QModelIndex& index)
{
    Q_UNUSED(index)
    QList<QAction*> actionList;
    actionList << &_enableEditMode;
    return actionList;
}

void BufferViewFilter::setFilterString(const QString string)
{
    beginResetModel();
    _filterString = string;
    endResetModel();
    enableEditMode(!string.isEmpty());
}

void BufferViewFilter::enableEditMode(bool enable)
{
    if (_editMode == enable) {
        return;
    }
    _editMode = enable;

    if (!config())
        return;

    if (enable == false) {
        addBuffers(_toAdd.values());
        QSet<BufferId>::const_iterator iter;
        for (iter = _toTempRemove.constBegin(); iter != _toTempRemove.constEnd(); ++iter) {
            if (config()->temporarilyRemovedBuffers().contains(*iter))
                continue;
            config()->requestRemoveBuffer(*iter);
        }
        for (iter = _toRemove.constBegin(); iter != _toRemove.constEnd(); ++iter) {
            if (config()->removedBuffers().contains(*iter))
                continue;
            config()->requestRemoveBufferPermanently(*iter);
        }
    }
    _toAdd.clear();
    _toTempRemove.clear();
    _toRemove.clear();

    invalidate();
}

Qt::ItemFlags BufferViewFilter::flags(const QModelIndex& index) const
{
    QModelIndex source_index = mapToSource(index);
    Qt::ItemFlags flags = sourceModel()->flags(source_index);
    if (config()) {
        BufferInfo::Type bufferType = (BufferInfo::Type)sourceModel()->data(source_index, NetworkModel::BufferTypeRole).toInt();

        // We need Status Buffers to be a drop target, to allow for rearranging buffers.
        // The Status Buffer "owns" the space between Channel/Query buffers in the tree.
        // This DOES mean that it looks like you can merge a buffer into the Status buffer, but that is restricted in BufferView::dropEvent().
        if (bufferType == BufferInfo::StatusBuffer) {
            // But only if the layout isn't locked!
            auto* clientConf = qobject_cast<ClientBufferViewConfig*>(config());
            if (clientConf && !clientConf->isLocked()) {
                flags |= Qt::ItemIsDropEnabled;
            }
        }

        // If we're in Edit Mode, everything except Status Buffers should be hideable.
        if (_editMode && bufferType != BufferInfo::StatusBuffer) {
            flags |= Qt::ItemIsUserCheckable;
        }
    }
    return flags;
}

bool BufferViewFilter::dropMimeData(const QMimeData* data, Qt::DropAction action, int row, int column, const QModelIndex& parent)
{
    if (!config() || !NetworkModel::mimeContainsBufferList(data))
        return QSortFilterProxyModel::dropMimeData(data, action, row, column, parent);

    NetworkId droppedNetworkId;
    QModelIndex source_parent = mapToSource(parent);
    if (sourceModel()->data(source_parent, NetworkModel::ItemTypeRole) == NetworkModel::NetworkItemType)
        droppedNetworkId = sourceModel()->data(source_parent, NetworkModel::NetworkIdRole).value<NetworkId>();

    QList<QPair<NetworkId, BufferId>> bufferList = NetworkModel::mimeDataToBufferList(data);
    BufferId bufferId;
    NetworkId networkId;
    int pos;
    for (int i = 0; i < bufferList.count(); i++) {
        networkId = bufferList[i].first;
        bufferId = bufferList[i].second;
        if (droppedNetworkId == networkId) {
            if (row < 0)
                row = 0;

            if (row < rowCount(parent)) {
                QModelIndex source_child = mapToSource(index(row, 0, parent));
                BufferId beforeBufferId = sourceModel()->data(source_child, NetworkModel::BufferIdRole).value<BufferId>();
                pos = config()->bufferList().indexOf(beforeBufferId);
                if (_sortOrder == Qt::DescendingOrder)
                    pos++;
            }
            else {
                if (_sortOrder == Qt::AscendingOrder)
                    pos = config()->bufferList().count();
                else
                    pos = 0;
            }

            if (config()->bufferList().contains(bufferId) && !config()->sortAlphabetically()) {
                if (config()->bufferList().indexOf(bufferId) < pos)
                    pos--;
                auto* clientConf = qobject_cast<ClientBufferViewConfig*>(config());
                if (!clientConf || !clientConf->isLocked())
                    config()->requestMoveBuffer(bufferId, pos);
            }
            else {
                config()->requestAddBuffer(bufferId, pos);
            }
        }
        else {
            addBuffer(bufferId);
        }
    }
    return true;
}

void BufferViewFilter::sort(int column, Qt::SortOrder order)
{
    _sortOrder = order;
    QSortFilterProxyModel::sort(column, order);
}

void BufferViewFilter::addBuffer(const BufferId& bufferId) const
{
    if (!config() || config()->bufferList().contains(bufferId))
        return;

    int pos = config()->bufferList().count();
    bool lt;
    for (int i = 0; i < config()->bufferList().count(); i++) {
        if (config() && config()->sortAlphabetically())
            lt = bufferIdLessThan(bufferId, config()->bufferList()[i]);
        else
            lt = bufferId < config()->bufferList()[i];

        if (lt) {
            pos = i;
            break;
        }
    }
    config()->requestAddBuffer(bufferId, pos);
}

void BufferViewFilter::addBuffers(const QList<BufferId>& bufferIds) const
{
    if (!config())
        return;

    QList<BufferId> bufferList = config()->bufferList();
    foreach (BufferId bufferId, bufferIds) {
        if (bufferList.contains(bufferId))
            continue;

        int pos = bufferList.count();
        bool lt;
        for (int i = 0; i < bufferList.count(); i++) {
            if (config() && config()->sortAlphabetically())
                lt = bufferIdLessThan(bufferId, bufferList[i]);
            else
                lt = bufferId < config()->bufferList()[i];

            if (lt) {
                pos = i;
                bufferList.insert(pos, bufferId);
                break;
            }
        }
        config()->requestAddBuffer(bufferId, pos);
    }
}

bool BufferViewFilter::filterAcceptBuffer(const QModelIndex& source_bufferIndex) const
{
    // no config -> "all buffers" -> accept everything
    if (!config())
        return true;

    BufferId bufferId = sourceModel()->data(source_bufferIndex, NetworkModel::BufferIdRole).value<BufferId>();
    Q_ASSERT(bufferId.isValid());

    int activityLevel = sourceModel()->data(source_bufferIndex, NetworkModel::BufferActivityRole).toInt();

    if (!config()->bufferList().contains(bufferId) && !_editMode) {
        // add the buffer if...
        if (config()->isInitialized() && !config()->removedBuffers().contains(bufferId)  // it hasn't been manually removed and either
            && ((config()->addNewBuffersAutomatically()
                 && !config()->temporarilyRemovedBuffers().contains(bufferId))  // is totally unknown to us (a new buffer)...
                || (config()->temporarilyRemovedBuffers().contains(bufferId)
                    && activityLevel > BufferInfo::OtherActivity))) {  // or was just temporarily hidden and has a new message waiting for us.
            addBuffer(bufferId);
        }
        // note: adding the buffer to the valid list does not temper with the following filters ("show only channels" and stuff)
        return false;
    }

    if (config()->networkId().isValid()
        && config()->networkId() != sourceModel()->data(source_bufferIndex, NetworkModel::NetworkIdRole).value<NetworkId>())
        return false;

    int allowedBufferTypes = config()->allowedBufferTypes();
    if (!config()->networkId().isValid())
        allowedBufferTypes &= ~BufferInfo::StatusBuffer;
    int bufferType = sourceModel()->data(source_bufferIndex, NetworkModel::BufferTypeRole).toInt();
    if (!(allowedBufferTypes & bufferType))
        return false;

    if (bufferType & BufferInfo::QueryBuffer && !_showServerQueries
        && sourceModel()->data(source_bufferIndex, Qt::DisplayRole).toString().contains('.')) {
        return false;
    }

    if (!_filterString.isEmpty()) {
        const BufferInfo info = qvariant_cast<BufferInfo>(Client::bufferModel()->data(source_bufferIndex, NetworkModel::BufferInfoRole));
        QString name = info.bufferName();
        if (name.contains(_filterString, Qt::CaseInsensitive)) {
            return true;
        }
        else {
            return false;
        }
    }

    // the following dynamic filters may not trigger if the buffer is currently selected.
    QModelIndex currentIndex = Client::bufferModel()->standardSelectionModel()->currentIndex();
    if (bufferId == Client::bufferModel()->data(currentIndex, NetworkModel::BufferIdRole).value<BufferId>())
        return true;

    if (config()->hideInactiveBuffers() && !sourceModel()->data(source_bufferIndex, NetworkModel::ItemActiveRole).toBool()
        && activityLevel <= BufferInfo::OtherActivity)
        return false;

    if (config()->minimumActivity() > activityLevel)
        return false;

    return true;
}

bool BufferViewFilter::filterAcceptNetwork(const QModelIndex& source_index) const
{
    if (!config())
        return true;

    if (config()->hideInactiveNetworks() && !(sourceModel()->data(source_index, NetworkModel::ItemActiveRole).toBool())) {
        return false;
    }

    if (!config()->networkId().isValid()) {
        return true;
    }
    else {
        return config()->networkId() == sourceModel()->data(source_index, NetworkModel::NetworkIdRole).value<NetworkId>();
    }
}

bool BufferViewFilter::filterAcceptsRow(int source_row, const QModelIndex& source_parent) const
{
    QModelIndex child = sourceModel()->index(source_row, 0, source_parent);

    if (!child.isValid()) {
        qWarning() << "filterAcceptsRow has been called with an invalid Child";
        return false;
    }

    NetworkModel::ItemType childType = (NetworkModel::ItemType)sourceModel()->data(child, NetworkModel::ItemTypeRole).toInt();
    switch (childType) {
    case NetworkModel::NetworkItemType:
        return filterAcceptNetwork(child);
    case NetworkModel::BufferItemType:
        return filterAcceptBuffer(child);
    default:
        return false;
    }
}

bool BufferViewFilter::lessThan(const QModelIndex& source_left, const QModelIndex& source_right) const
{
    int leftItemType = sourceModel()->data(source_left, NetworkModel::ItemTypeRole).toInt();
    int rightItemType = sourceModel()->data(source_right, NetworkModel::ItemTypeRole).toInt();
    int itemType = leftItemType & rightItemType;
    switch (itemType) {
    case NetworkModel::NetworkItemType:
        return networkLessThan(source_left, source_right);
    case NetworkModel::BufferItemType:
        return bufferLessThan(source_left, source_right);
    default:
        return QSortFilterProxyModel::lessThan(source_left, source_right);
    }
}

bool BufferViewFilter::bufferLessThan(const QModelIndex& source_left, const QModelIndex& source_right) const
{
    BufferId leftBufferId = sourceModel()->data(source_left, NetworkModel::BufferIdRole).value<BufferId>();
    BufferId rightBufferId = sourceModel()->data(source_right, NetworkModel::BufferIdRole).value<BufferId>();
    // If filtering, prioritize relevant items first
    if (!_filterString.isEmpty()) {
        // Get names of the buffers
        QString leftBufferName = sourceModel()->data(source_left, NetworkModel::BufferInfoRole).value<BufferInfo>().bufferName();
        QString rightBufferName = sourceModel()->data(source_right, NetworkModel::BufferInfoRole).value<BufferInfo>().bufferName();
        // Check if there's any differences across types, most important first
        if ((QString::compare(leftBufferName, _filterString, Qt::CaseInsensitive) == 0)
            != (QString::compare(rightBufferName, _filterString, Qt::CaseInsensitive) == 0)) {
            // One of these buffers is an exact match with the filter string, while the other isn't
            // Prioritize whichever one is the exact match
            // (If left buffer is exact, return true to set it as less than right)
            return (QString::compare(leftBufferName, _filterString, Qt::CaseInsensitive) == 0);
        }
        else if (leftBufferName.startsWith(_filterString, Qt::CaseInsensitive)
                 != rightBufferName.startsWith(_filterString, Qt::CaseInsensitive)) {
            // One of these buffers starts with the filter string, while the other doesn't
            // Prioritize whichever one starts with the filter string
            // (If left buffer starts with, return true to set it as less than right)
            return leftBufferName.startsWith(_filterString, Qt::CaseInsensitive);
        }
        // Otherwise, do the normal sorting (sorting happens within each priority bracket)
    }
    if (config()) {
        int leftPos = config()->bufferList().indexOf(leftBufferId);
        int rightPos = config()->bufferList().indexOf(rightBufferId);
        if (leftPos == -1 && rightPos == -1)
            return QSortFilterProxyModel::lessThan(source_left, source_right);
        if (leftPos == -1 || rightPos == -1)
            return !(leftPos < rightPos);
        return leftPos < rightPos;
    }
    else
        return bufferIdLessThan(leftBufferId, rightBufferId);
}

bool BufferViewFilter::networkLessThan(const QModelIndex& source_left, const QModelIndex& source_right) const
{
    // NetworkId leftNetworkId = sourceModel()->data(source_left, NetworkModel::NetworkIdRole).value<NetworkId>();
    // NetworkId rightNetworkId = sourceModel()->data(source_right, NetworkModel::NetworkIdRole).value<NetworkId>();

    return QSortFilterProxyModel::lessThan(source_left, source_right);
}

QVariant BufferViewFilter::data(const QModelIndex& index, int role) const
{
    switch (role) {
    case Qt::FontRole:
    case Qt::ForegroundRole:
    case Qt::BackgroundRole:
    case Qt::DecorationRole:
        if ((config() && config()->disableDecoration()))
            return QVariant();
        return GraphicalUi::uiStyle()->bufferViewItemData(mapToSource(index), role);
    case Qt::CheckStateRole:
        return checkedState(index);
    default:
        return QSortFilterProxyModel::data(index, role);
    }
}

QVariant BufferViewFilter::checkedState(const QModelIndex& index) const
{
    if (!_editMode || !config())
        return QVariant();

    QModelIndex source_index = mapToSource(index);
    if (source_index == QModelIndex() || sourceModel()->data(source_index, NetworkModel::ItemTypeRole) == NetworkModel::NetworkItemType)
        return QVariant();

    BufferId bufferId = sourceModel()->data(source_index, NetworkModel::BufferIdRole).value<BufferId>();
    if (_toAdd.contains(bufferId))
        return Qt::Checked;

    if (_toTempRemove.contains(bufferId))
        return Qt::PartiallyChecked;

    if (_toRemove.contains(bufferId))
        return Qt::Unchecked;

    if (config()->bufferList().contains(bufferId))
        return Qt::Checked;

    if (config()->temporarilyRemovedBuffers().contains(bufferId))
        return Qt::PartiallyChecked;

    return Qt::Unchecked;
}

bool BufferViewFilter::setData(const QModelIndex& index, const QVariant& value, int role)
{
    switch (role) {
    case Qt::CheckStateRole:
        return setCheckedState(index, Qt::CheckState(value.toInt()));
    default:
        return QSortFilterProxyModel::setData(index, value, role);
    }
}

bool BufferViewFilter::setCheckedState(const QModelIndex& index, Qt::CheckState state)
{
    QModelIndex source_index = mapToSource(index);
    BufferId bufferId = sourceModel()->data(source_index, NetworkModel::BufferIdRole).value<BufferId>();
    if (!bufferId.isValid())
        return false;

    switch (state) {
    case Qt::Unchecked:
        _toAdd.remove(bufferId);
        _toTempRemove.remove(bufferId);
        _toRemove << bufferId;
        break;
    case Qt::PartiallyChecked:
        _toAdd.remove(bufferId);
        _toTempRemove << bufferId;
        _toRemove.remove(bufferId);
        break;
    case Qt::Checked:
        _toAdd << bufferId;
        _toTempRemove.remove(bufferId);
        _toRemove.remove(bufferId);
        break;
    default:
        return false;
    }
    emit dataChanged(index, index);
    return true;
}

bool BufferViewFilter::bufferIdLessThan(const BufferId& left, const BufferId& right)
{
    Q_CHECK_PTR(Client::networkModel());
    if (!Client::networkModel())
        return true;

    QModelIndex leftIndex = Client::networkModel()->bufferIndex(left);
    QModelIndex rightIndex = Client::networkModel()->bufferIndex(right);

    int leftType = Client::networkModel()->data(leftIndex, NetworkModel::BufferTypeRole).toInt();
    int rightType = Client::networkModel()->data(rightIndex, NetworkModel::BufferTypeRole).toInt();

    if (leftType != rightType)
        return leftType < rightType;
    else
        return QString::compare(Client::networkModel()->data(leftIndex, Qt::DisplayRole).toString(),
                                Client::networkModel()->data(rightIndex, Qt::DisplayRole).toString(),
                                Qt::CaseInsensitive)
               < 0;
}
