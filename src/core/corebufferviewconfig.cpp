// SPDX-FileCopyrightText: 2005-2025 Quassel Project <devel@quassel-irc.org>
// SPDX-License-Identifier: GPL-2.0-or-later

#include "corebufferviewconfig.h"

CoreBufferViewConfig::CoreBufferViewConfig(int bufferViewId, QObject* parent)
    : BufferViewConfig(bufferViewId, parent)
{
    setAllowClientUpdates(true);
}

CoreBufferViewConfig::CoreBufferViewConfig(int bufferViewId, const QVariantMap& properties, QObject* parent)
    : BufferViewConfig(bufferViewId, properties, parent)
{
    setAllowClientUpdates(true);
}
