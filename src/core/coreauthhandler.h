// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

#include "authhandler.h"
#include "metricsserver.h"
#include "peerfactory.h"
#include "proxyline.h"
#include "remotepeer.h"
#include "types.h"

class CoreAuthHandler : public AuthHandler
{
    Q_OBJECT

public:
    CoreAuthHandler(QSslSocket* socket, QObject* parent = nullptr);

    QHostAddress hostAddress() const;
    bool isLocal() const override;

signals:
    void handshakeComplete(RemotePeer* peer, UserId uid);

private:
    using AuthHandler::handle;

    void handle(const QuasselProtocol::RegisterClient& msg) override;
    void handle(const QuasselProtocol::SetupData& msg) override;
    void handle(const QuasselProtocol::Login& msg) override;

    void setPeer(RemotePeer* peer);
    void startSsl();

    bool checkClientRegistered();

private slots:
    void onReadyRead();

    void onSslErrors();

    // only in legacy mode
    void onProtocolVersionMismatch(int actual, int expected);

private:
    RemotePeer* _peer;
    MetricsServer* _metricsServer;

    bool _proxyReceived;
    ProxyLine _proxyLine;
    bool _useProxyLine;
    bool _magicReceived;
    bool _legacy;
    bool _clientRegistered;
    quint8 _connectionFeatures;
    QVector<PeerFactory::ProtoDescriptor> _supportedProtos;
};
