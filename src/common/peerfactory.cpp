// SPDX-License-Identifier: GPL-2.0-or-later

#include "peerfactory.h"

#include "protocols/datastream/datastreampeer.h"
#include "protocols/legacy/legacypeer.h"

PeerFactory::ProtoList PeerFactory::supportedProtocols()
{
    ProtoList result;
    result.append(ProtoDescriptor(QuasselProtocol::DataStreamProtocol, DataStreamPeer::supportedFeatures()));
    result.append(ProtoDescriptor(QuasselProtocol::LegacyProtocol, 0));
    return result;
}

RemotePeer* PeerFactory::createPeer(
    const ProtoDescriptor& protocol, AuthHandler* authHandler, QTcpSocket* socket, Compressor::CompressionLevel level, QObject* parent)
{
    return createPeer(ProtoList() << protocol, authHandler, socket, level, parent);
}

RemotePeer* PeerFactory::createPeer(
    const ProtoList& protocols, AuthHandler* authHandler, QTcpSocket* socket, Compressor::CompressionLevel level, QObject* parent)
{
    foreach (const ProtoDescriptor& protodesc, protocols) {
        QuasselProtocol::Type proto = protodesc.first;
        quint16 features = protodesc.second;
        switch (proto) {
        case QuasselProtocol::LegacyProtocol:
            return new LegacyPeer(authHandler, socket, level, parent);
        case QuasselProtocol::DataStreamProtocol:
            if (DataStreamPeer::acceptsFeatures(features))
                return new DataStreamPeer(authHandler, socket, features, level, parent);
            break;
        default:
            break;
        }
    }

    return nullptr;
}
