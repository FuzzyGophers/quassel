// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

#include "client-export.h"

#include "bufferviewmanager.h"

class ClientBufferViewConfig;
class BufferViewOverlay;

class CLIENT_EXPORT ClientBufferViewManager : public BufferViewManager
{
    Q_OBJECT

public:
    ClientBufferViewManager(SignalProxy* proxy, QObject* parent = nullptr);

    QList<ClientBufferViewConfig*> clientBufferViewConfigs() const;
    ClientBufferViewConfig* clientBufferViewConfig(int bufferViewId) const;

public slots:
    void setInitialized() override;

protected:
    BufferViewConfig* bufferViewConfigFactory(int bufferViewConfigId) override;
};
