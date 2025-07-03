// SPDX-FileCopyrightText: 2005-2025 Quassel Project <devel@quassel-irc.org>
// SPDX-License-Identifier: GPL-2.0-or-later

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
