// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

#include "bufferviewmanager.h"

class CoreSession;

class CoreBufferViewManager : public BufferViewManager
{
    Q_OBJECT

public:
    CoreBufferViewManager(SignalProxy* proxy, CoreSession* parent);

public slots:
    void requestCreateBufferView(const QVariantMap& properties) override;
    void requestCreateBufferViews(const QVariantList& properties) override;
    void requestDeleteBufferView(int bufferViewId) override;
    void requestDeleteBufferViews(const QVariantList& bufferViews) override;

    void saveBufferViews();

private:
    CoreSession* _coreSession;
};
