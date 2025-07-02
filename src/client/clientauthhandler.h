// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

#include "authhandler.h"
#include "compressor.h"
#include "coreaccount.h"

class QSslSocket;

class RemotePeer;

class ClientAuthHandler : public AuthHandler
{
    Q_OBJECT

public:
    enum DigestVersion
    {
        Md5,
        Sha2_512,
        Latest = Sha2_512
    };

    ClientAuthHandler(CoreAccount account, QObject* parent = nullptr);

    Peer* peer() const;

public slots:
    void connectToCore();

    void login(const QString& previousError = QString());
    void login(const QString& user, const QString& password, bool remember);
    void setupCore(const QuasselProtocol::SetupData& setupData);

signals:
    void statusMessage(const QString& message);
    void errorMessage(const QString& message);
    void errorPopup(const QString& message);
    void transferProgress(int current, int max);

    void requestDisconnect(const QString& errorString = QString(), bool wantReconnect = false);

    void connectionReady();
    void loginSuccessful(const CoreAccount& account);
    void handshakeComplete(RemotePeer* peer, const QuasselProtocol::SessionState& sessionState);

    // These signals MUST be handled synchronously!
    void userAuthenticationRequired(CoreAccount* account, bool* valid, const QString& errorMessage = QString());
    void handleNoSslInClient(bool* accepted);
    void handleNoSslInCore(bool* accepted);
    void handleSslErrors(const QSslSocket* socket, bool* accepted, bool* permanently);

    void encrypted(bool isEncrypted = true);
    void startCoreSetup(const QVariantList& backendInfo, const QVariantList& authenticatorInfo);
    void coreSetupSuccessful();
    void coreSetupFailed(const QString& error);

private:
    using AuthHandler::handle;

    void handle(const QuasselProtocol::ClientDenied& msg) override;
    void handle(const QuasselProtocol::ClientRegistered& msg) override;
    void handle(const QuasselProtocol::SetupFailed& msg) override;
    void handle(const QuasselProtocol::SetupDone& msg) override;
    void handle(const QuasselProtocol::LoginFailed& msg) override;
    void handle(const QuasselProtocol::LoginSuccess& msg) override;
    void handle(const QuasselProtocol::SessionState& msg) override;

    void setPeer(RemotePeer* peer);
    void checkAndEnableSsl(bool coreSupportsSsl);
    void startRegistration();

private slots:
    void onSocketConnected();
    void onSocketStateChanged(QAbstractSocket::SocketState state);
    void onSocketError(QAbstractSocket::SocketError) override;
    void onSocketDisconnected() override;
    void onReadyRead();

    void onSslSocketEncrypted();
    void onSslErrors();

    void onProtocolVersionMismatch(int actual, int expected);

    void onConnectionReady();

private:
    RemotePeer* _peer;
    bool _coreConfigured;
    QVariantList _backendInfo;
    QVariantList _authenticatorInfo;
    CoreAccount _account;
    bool _probing;
    bool _legacy;
    quint8 _connectionFeatures;
};
