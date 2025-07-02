// SPDX-License-Identifier: GPL-2.0-or-later

#include "bufferviewmanager.h"

#include "bufferviewconfig.h"
#include "signalproxy.h"

BufferViewManager::BufferViewManager(SignalProxy* proxy, QObject* parent)
    : SyncableObject(parent)
    , _proxy(proxy)
{
    _proxy->synchronize(this);
}

BufferViewConfig* BufferViewManager::bufferViewConfig(int bufferViewId) const
{
    if (_bufferViewConfigs.contains(bufferViewId))
        return _bufferViewConfigs[bufferViewId];
    else
        return nullptr;
}

BufferViewConfig* BufferViewManager::bufferViewConfigFactory(int bufferViewConfigId)
{
    return new BufferViewConfig(bufferViewConfigId, this);
}

void BufferViewManager::addBufferViewConfig(int bufferViewConfigId)
{
    if (_bufferViewConfigs.contains(bufferViewConfigId)) {
        return;
    }

    addBufferViewConfig(bufferViewConfigFactory(bufferViewConfigId));
}

void BufferViewManager::addBufferViewConfig(BufferViewConfig* config)
{
    if (_bufferViewConfigs.contains(config->bufferViewId())) {
        delete config;
        return;
    }

    _proxy->synchronize(config);
    _bufferViewConfigs[config->bufferViewId()] = config;
    int bufferViewId = config->bufferViewId();
    SYNC_OTHER(addBufferViewConfig, ARG(bufferViewId))
    emit bufferViewConfigAdded(bufferViewId);
}

void BufferViewManager::deleteBufferViewConfig(int bufferViewConfigId)
{
    if (!_bufferViewConfigs.contains(bufferViewConfigId))
        return;

    _bufferViewConfigs[bufferViewConfigId]->deleteLater();
    _bufferViewConfigs.remove(bufferViewConfigId);
    SYNC(ARG(bufferViewConfigId))
    emit bufferViewConfigDeleted(bufferViewConfigId);
}

QVariantList BufferViewManager::initBufferViewIds() const
{
    QVariantList bufferViewIds;
    BufferViewConfigHash::const_iterator iter = _bufferViewConfigs.constBegin();
    BufferViewConfigHash::const_iterator iterEnd = _bufferViewConfigs.constEnd();
    while (iter != iterEnd) {
        bufferViewIds << (*iter)->bufferViewId();
        ++iter;
    }
    return bufferViewIds;
}

void BufferViewManager::initSetBufferViewIds(const QVariantList bufferViewIds)
{
    for (auto&& id : bufferViewIds) {
        addBufferViewConfig(id.value<int>());
    }
}
