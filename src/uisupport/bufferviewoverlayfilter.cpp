// SPDX-License-Identifier: GPL-2.0-or-later

#include "bufferviewoverlayfilter.h"

#include "bufferviewoverlay.h"
#include "networkmodel.h"
#include "types.h"

BufferViewOverlayFilter::BufferViewOverlayFilter(QAbstractItemModel* model, BufferViewOverlay* overlay)
    : QSortFilterProxyModel(model)
    , _overlay(nullptr)
{
    setOverlay(overlay);
    setSourceModel(model);

    setDynamicSortFilter(true);
}

void BufferViewOverlayFilter::setOverlay(BufferViewOverlay* overlay)
{
    if (_overlay == overlay)
        return;

    if (_overlay) {
        disconnect(_overlay, nullptr, this, nullptr);
    }

    _overlay = overlay;

    if (!overlay) {
        invalidate();
        return;
    }

    connect(overlay, &QObject::destroyed, this, &BufferViewOverlayFilter::overlayDestroyed);
    connect(overlay, &BufferViewOverlay::hasChanged, this, &QSortFilterProxyModel::invalidate);
    invalidate();
}

void BufferViewOverlayFilter::overlayDestroyed()
{
    setOverlay(nullptr);
}

bool BufferViewOverlayFilter::filterAcceptsRow(int source_row, const QModelIndex& source_parent) const
{
    if (!_overlay)
        return false;

    QModelIndex source_bufferIndex = sourceModel()->index(source_row, 0, source_parent);

    if (!source_bufferIndex.isValid()) {
        qWarning() << "filterAcceptsRow has been called with an invalid Child";
        return false;
    }

    NetworkModel::ItemType itemType = (NetworkModel::ItemType)sourceModel()->data(source_bufferIndex, NetworkModel::ItemTypeRole).toInt();

    NetworkId networkId = sourceModel()->data(source_bufferIndex, NetworkModel::NetworkIdRole).value<NetworkId>();
    if (!_overlay->networkIds().contains(networkId) && !_overlay->allNetworks()) {
        return false;
    }
    else if (itemType == NetworkModel::NetworkItemType) {
        // network items don't need further checks.
        return true;
    }

    int activityLevel = sourceModel()->data(source_bufferIndex, NetworkModel::BufferActivityRole).toInt();
    if (_overlay->minimumActivity() > activityLevel)
        return false;

    int bufferType = sourceModel()->data(source_bufferIndex, NetworkModel::BufferTypeRole).toInt();
    if (!(_overlay->allowedBufferTypes() & bufferType))
        return false;

    BufferId bufferId = sourceModel()->data(source_bufferIndex, NetworkModel::BufferIdRole).value<BufferId>();
    Q_ASSERT(bufferId.isValid());

    if (_overlay->bufferIds().contains(bufferId))
        return true;

    if (_overlay->tempRemovedBufferIds().contains(bufferId))
        return activityLevel > BufferInfo::OtherActivity;

    if (_overlay->removedBufferIds().contains(bufferId))
        return false;

    // the buffer is not known to us
    qDebug() << "BufferViewOverlayFilter::filterAcceptsRow()" << bufferId << "is unknown!";
    return false;
}
