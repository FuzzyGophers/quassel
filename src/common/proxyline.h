// SPDX-FileCopyrightText: 2005-2025 Quassel Project <devel@quassel-irc.org>
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

#include "common-export.h"

#include <QAbstractSocket>
#include <QByteArray>
#include <QHostAddress>

struct COMMON_EXPORT ProxyLine
{
    QAbstractSocket::NetworkLayerProtocol protocol = QAbstractSocket::UnknownNetworkLayerProtocol;
    QHostAddress sourceHost;
    uint16_t sourcePort;
    QHostAddress targetHost;
    uint16_t targetPort;

    static ProxyLine parseProxyLine(const QByteArray& line);
    friend COMMON_EXPORT QDebug operator<<(QDebug dbg, const ProxyLine& p);
};
