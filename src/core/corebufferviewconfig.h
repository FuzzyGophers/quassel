// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

#include "bufferviewconfig.h"

class CoreBufferViewConfig : public BufferViewConfig
{
    Q_OBJECT

public:
    CoreBufferViewConfig(int bufferViewId, QObject* parent = nullptr);
    CoreBufferViewConfig(int bufferViewId, const QVariantMap& properties, QObject* parent = nullptr);

public slots:
    inline void requestSetBufferViewName(const QString& bufferViewName) override { setBufferViewName(bufferViewName); }
    inline void requestRemoveBuffer(const BufferId& bufferId) override { removeBuffer(bufferId); }
    inline void requestRemoveBufferPermanently(const BufferId& bufferId) override { removeBufferPermanently(bufferId); }
    inline void requestAddBuffer(const BufferId& bufferId, int pos) override { addBuffer(bufferId, pos); }
    inline void requestMoveBuffer(const BufferId& bufferId, int pos) override { moveBuffer(bufferId, pos); }
};
