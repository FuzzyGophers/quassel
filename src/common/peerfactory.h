/***************************************************************************
 *   Copyright (C) 2005-2022 by the Quassel Project                        *
 *   devel@quassel-irc.org                                                 *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) version 3.                                           *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   You should have received a copy of the GNU General Public License     *
 *   along with this program; if not, write to the                         *
 *   Free Software Foundation, Inc.,                                       *
 *   51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.         *
 ***************************************************************************/

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
