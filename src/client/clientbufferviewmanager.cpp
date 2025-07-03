// SPDX-FileCopyrightText: 2005-2025 Quassel Project <devel@quassel-irc.org>
// SPDX-License-Identifier: GPL-2.0-or-later

#include "clientbufferviewmanager.h"

#include "client.h"
#include "clientbufferviewconfig.h"
#include "networkmodel.h"

ClientBufferViewManager::ClientBufferViewManager(SignalProxy* proxy, QObject* parent)
    : BufferViewManager(proxy, parent)
{}

BufferViewConfig* ClientBufferViewManager::bufferViewConfigFactory(int bufferViewConfigId)
{
    return new ClientBufferViewConfig(bufferViewConfigId, this);
}

QList<ClientBufferViewConfig*> ClientBufferViewManager::clientBufferViewConfigs() const
{
    QList<ClientBufferViewConfig*> clientConfigs;
    foreach (BufferViewConfig* config, bufferViewConfigs()) {
        clientConfigs << static_cast<ClientBufferViewConfig*>(config);
    }
    return clientConfigs;
}

ClientBufferViewConfig* ClientBufferViewManager::clientBufferViewConfig(int bufferViewId) const
{
    return static_cast<ClientBufferViewConfig*>(bufferViewConfig(bufferViewId));
}

void ClientBufferViewManager::setInitialized()
{
    if (bufferViewConfigs().isEmpty()) {
        BufferViewConfig config(-1);
        config.setBufferViewName(tr("All Chats"));
        config.setBufferList(Client::networkModel()->allBufferIdsSorted());
        requestCreateBufferView(config.toVariantMap());
    }
    BufferViewManager::setInitialized();
}
