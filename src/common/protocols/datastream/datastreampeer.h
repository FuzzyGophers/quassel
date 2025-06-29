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

#ifndef DATASTREAMPEER_H
#define DATASTREAMPEER_H

#include "../../remotepeer.h"

class QDataStream;

class DataStreamPeer : public RemotePeer
{
    Q_OBJECT

public:
    enum RequestType
    {
        Sync = 1,
        RpcCall,
        InitRequest,
        InitData,
        HeartBeat,
        HeartBeatReply
    };

    DataStreamPeer(AuthHandler* authHandler, QTcpSocket* socket, quint16 features, Compressor::CompressionLevel level, QObject* parent = nullptr);

    QuasselProtocol::Type protocol() const override { return QuasselProtocol::DataStreamProtocol; }
    QString protocolName() const override { return "the DataStream protocol"; }

    static quint16 supportedFeatures();
    static bool acceptsFeatures(quint16 peerFeatures);
    quint16 enabledFeatures() const override;

    void dispatch(const QuasselProtocol::RegisterClient& msg) override;
    void dispatch(const QuasselProtocol::ClientDenied& msg) override;
    void dispatch(const QuasselProtocol::ClientRegistered& msg) override;
    void dispatch(const QuasselProtocol::SetupData& msg) override;
    void dispatch(const QuasselProtocol::SetupFailed& msg) override;
    void dispatch(const QuasselProtocol::SetupDone& msg) override;
    void dispatch(const QuasselProtocol::Login& msg) override;
    void dispatch(const QuasselProtocol::LoginFailed& msg) override;
    void dispatch(const QuasselProtocol::LoginSuccess& msg) override;
    void dispatch(const QuasselProtocol::SessionState& msg) override;

    void dispatch(const QuasselProtocol::SyncMessage& msg) override;
    void dispatch(const QuasselProtocol::RpcCall& msg) override;
    void dispatch(const QuasselProtocol::InitRequest& msg) override;
    void dispatch(const QuasselProtocol::InitData& msg) override;

    void dispatch(const QuasselProtocol::HeartBeat& msg) override;
    void dispatch(const QuasselProtocol::HeartBeatReply& msg) override;

signals:
    void protocolError(const QString& errorString);

private:
    using RemotePeer::writeMessage;
    void writeMessage(const QVariantMap& handshakeMsg);
    void writeMessage(const QVariantList& sigProxyMsg);
    void processMessage(const QByteArray& msg) override;

    void handleHandshakeMessage(const QVariantList& mapData);
    void handlePackedFunc(const QVariantList& packedFunc);
    void dispatchPackedFunc(const QVariantList& packedFunc);
};

#endif
