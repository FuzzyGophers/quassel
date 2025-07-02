// SPDX-License-Identifier: GPL-2.0-or-later

#include "clientbufferviewconfig.h"

ClientBufferViewConfig::ClientBufferViewConfig(int bufferViewId, QObject* parent)
    : BufferViewConfig(bufferViewId, parent)
    , _locked(false)
{
    connect(this, &SyncableObject::initDone, this, &ClientBufferViewConfig::ensureDecoration);
}

// currently we don't have a possibility to configure disableDecoration
// if we have an old config this value can be true which is... bad.
// so we upgrade the core stored bufferViewConfig.
// This can be removed with the next release
void ClientBufferViewConfig::ensureDecoration()
{
    if (!disableDecoration())
        return;
    setDisableDecoration(false);
    requestUpdate(toVariantMap());
}
