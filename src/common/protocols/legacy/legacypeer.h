// SPDX-FileCopyrightText: 2005-2025 Quassel Project <devel@quassel-irc.org>
// SPDX-License-Identifier: GPL-2.0-or-later

#ifndef LEGACYPEER_H
#define LEGACYPEER_H

#include "../../remotepeer.h"

class LegacyPeer : public RemotePeer
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

    LegacyPeer(AuthHandler* authHandler, QTcpSocket* socket, Compressor::CompressionLevel level, QObject* parent = nullptr);

    QuasselProtocol::Type protocol() const override { return QuasselProtocol::LegacyProtocol; }
    QString protocolName() const override { return "the legacy protocol"; }

    void setSignalProxy(SignalProxy* proxy) override;

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
    void writeMessage(const QVariant& item);
    void processMessage(const QByteArray& msg) override;

    void handleHandshakeMessage(const QVariant& msg);
    void handlePackedFunc(const QVariant& packedFunc);
    void dispatchPackedFunc(const QVariantList& packedFunc);

    void toLegacyIrcUsersAndChannels(QVariantMap& initData);
    void fromLegacyIrcUsersAndChannels(QVariantMap& initData);

    bool _useCompression;
};

#endif
