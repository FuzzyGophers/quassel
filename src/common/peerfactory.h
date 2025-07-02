// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

#include "common-export.h"

#include <QPair>

#include "compressor.h"
#include "protocol.h"

class QObject;
class QTcpSocket;

class AuthHandler;
class RemotePeer;

class COMMON_EXPORT PeerFactory
{
public:
    // second value is the protocol-specific features
    using ProtoDescriptor = QPair<QuasselProtocol::Type, quint16>;
    using ProtoList = QVector<ProtoDescriptor>;

    static ProtoList supportedProtocols();

    static RemotePeer* createPeer(const ProtoDescriptor& protocol,
                                  AuthHandler* authHandler,
                                  QTcpSocket* socket,
                                  Compressor::CompressionLevel level,
                                  QObject* parent = nullptr);
    static RemotePeer* createPeer(const ProtoList& protocols,
                                  AuthHandler* authHandler,
                                  QTcpSocket* socket,
                                  Compressor::CompressionLevel level,
                                  QObject* parent = nullptr);
};
