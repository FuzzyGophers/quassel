// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

#include "common-export.h"

#include <QHash>
#include <QList>

#include "syncableobject.h"

class BufferViewConfig;
class SignalProxy;

class COMMON_EXPORT BufferViewManager : public SyncableObject
{
    Q_OBJECT
    SYNCABLE_OBJECT

public:
    BufferViewManager(SignalProxy* proxy, QObject* parent = nullptr);

    inline QList<BufferViewConfig*> bufferViewConfigs() const { return _bufferViewConfigs.values(); }
    BufferViewConfig* bufferViewConfig(int bufferViewId) const;

public slots:
    QVariantList initBufferViewIds() const;
    void initSetBufferViewIds(const QVariantList bufferViewIds);

    void addBufferViewConfig(int bufferViewConfigId);
    void deleteBufferViewConfig(int bufferViewConfigId);

    virtual inline void requestCreateBufferView(const QVariantMap& properties) { REQUEST(ARG(properties)) }
    virtual inline void requestCreateBufferViews(const QVariantList& properties) { REQUEST(ARG(properties)) }
    virtual inline void requestDeleteBufferView(int bufferViewId) { REQUEST(ARG(bufferViewId)) }
    virtual inline void requestDeleteBufferViews(const QVariantList& bufferViews) { REQUEST(ARG(bufferViews)) }

    signals : void bufferViewConfigAdded(int bufferViewConfigId);
    void bufferViewConfigDeleted(int bufferViewConfigId);
    //   void createBufferViewRequested(const QVariantMap &properties);
    //   void createBufferViewsRequested(const QVariantList &properties);
    //   void deleteBufferViewRequested(int bufferViewId);
    //   void deleteBufferViewsRequested(const QVariantList &bufferViews);

protected:
    using BufferViewConfigHash = QHash<int, BufferViewConfig*>;
    inline const BufferViewConfigHash& bufferViewConfigHash() { return _bufferViewConfigs; }
    virtual BufferViewConfig* bufferViewConfigFactory(int bufferViewConfigId);

    void addBufferViewConfig(BufferViewConfig* config);

private:
    BufferViewConfigHash _bufferViewConfigs;
    SignalProxy* _proxy;
};
