// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

#include "client-export.h"

#include <QObject>

#include "types.h"

class BufferViewConfig;
class ClientBufferViewConfig;

class CLIENT_EXPORT BufferViewOverlay : public QObject
{
    Q_OBJECT

public:
    BufferViewOverlay(QObject* parent = nullptr);

    inline const QSet<int>& bufferViewIds() { return _bufferViewIds; }
    bool allNetworks();

    const QSet<NetworkId>& networkIds();
    const QSet<BufferId>& bufferIds();
    const QSet<BufferId>& removedBufferIds();
    const QSet<BufferId>& tempRemovedBufferIds();

    int allowedBufferTypes();
    int minimumActivity();

    inline bool isInitialized() { return _uninitializedViewCount == 0; }

public slots:
    void addView(int viewId);
    void removeView(int viewId);

    void reset();
    void save();
    void restore();

    // updates propagated from the actual views
    void update();

signals:
    void hasChanged();
    void initDone();

protected:
    void customEvent(QEvent* event) override;

private slots:
    void viewInitialized();
    void viewInitialized(BufferViewConfig* config);

private:
    void updateHelper();
    QSet<BufferId> filterBuffersByConfig(const QList<BufferId>& buffers, const BufferViewConfig* config);

    bool _aboutToUpdate{false};

    QSet<int> _bufferViewIds;
    int _uninitializedViewCount{0};

    QSet<NetworkId> _networkIds;
    int _allowedBufferTypes{0};
    int _minimumActivity{0};

    QSet<BufferId> _buffers;
    QSet<BufferId> _removedBuffers;
    QSet<BufferId> _tempRemovedBuffers;

    static const int _updateEventId;
};
