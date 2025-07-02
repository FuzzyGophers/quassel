// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

#include <QAbstractSocket>
#include <QByteArray>
#include <QHostAddress>

#include "common-export.h"

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
