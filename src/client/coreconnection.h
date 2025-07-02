// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

#include "client-export.h"

#include <QNetworkInformation>
#include <QPointer>
#include <QSslSocket>
#include <QTimer>

#include "coreaccount.h"
#include "remotepeer.h"
#include "types.h"

class ClientAuthHandler;
class CoreAccountModel;
class InternalPeer;
class Network;
class Peer;
class SignalProxy;

class CLIENT_EXPORT CoreConnection : public QObject
{
    Q_OBJECT

public:
    enum ConnectionState
    {
        Disconnected,
        Connecting,
        Connected,
        Synchronizing,
        Synchronized
    };

    CoreConnection(QObject* parent = nullptr);

    void init();

    bool isConnected() const;
    ConnectionState state() const;
    CoreAccount currentAccount() const;

    bool isEncrypted() const;
    bool isLocalConnection() const;

    int progressMinimum() const;
    int progressMaximum() const;
    int progressValue() const;
    QString progressText() const;

    //! Check if we consider the last connect as reconnect
    bool wasReconnect() const { return _wasReconnect; }

    QPointer<Peer> peer() const;

public slots:
    bool connectToCore(AccountId = 0);
    void reconnectToCore();
    void disconnectFromCore();
    void internalSessionStateReceived(const QuasselProtocol::SessionState& sessionState);

    void setupCore(const QuasselProtocol::SetupData& setupData);

signals:
    void stateChanged(CoreConnection::ConnectionState);
    void encrypted(bool isEncrypted = true);
    void synchronized();
    void lagUpdated(int msecs);

    void connectionError(const QString& errorMsg);
    void connectionErrorPopup(const QString& errorMsg);
    void connectionMsg(const QString& msg);
    void disconnected();

    void progressRangeChanged(int minimum, int maximum);
    void progressValueChanged(int value);
    void progressTextChanged(const QString&);

    void startCoreSetup(const QVariantList& backendInfo, const QVariantList& authenticatorInfo);
    void coreSetupSuccess();
    void coreSetupFailed(const QString& error);

    void connectToInternalCore(QPointer<InternalPeer> connection);

    // These signals MUST be handled synchronously!
    void userAuthenticationRequired(CoreAccount*, bool* valid, const QString& errorMessage = QString());
    void handleNoSslInClient(bool* accepted);
    void handleNoSslInCore(bool* accepted);
    void handleSslErrors(const QSslSocket* socket, bool* accepted, bool* permanently);

private slots:
    void connectToCurrentAccount();
    void disconnectFromCore(const QString& errorString, bool wantReconnect = true);

    void coreSocketError(QAbstractSocket::SocketError error, const QString& errorString);
    void coreSocketDisconnected();

    // for sync progress
    void networkInitDone();
    void checkSyncState();

    void loginToCore(const QString& user, const QString& password, bool remember);  // for config wizard
    void syncToCore(const QuasselProtocol::SessionState& sessionState);

    void resetConnection(bool wantReconnect = false);

    void onConnectionReady();
    void onLoginSuccessful(const CoreAccount& account);
    void onHandshakeComplete(RemotePeer* peer, const QuasselProtocol::SessionState& sessionState);

    void updateProgress(int value, int maximum);
    void setProgressText(const QString& text);
    void setProgressValue(int value);
    void setProgressMinimum(int minimum);
    void setProgressMaximum(int maximum);

    void setState(ConnectionState state);

    void networkDetectionModeChanged(const QVariant& mode);
    void pingTimeoutIntervalChanged(const QVariant& interval);
    void reconnectIntervalChanged(const QVariant& interval);
    void reconnectTimeout();

    void onlineStateChanged(QNetworkInformation::Reachability reachability);

private:
    QPointer<ClientAuthHandler> _authHandler;
    QPointer<Peer> _peer;
    ConnectionState _state{Disconnected};

    QTimer _reconnectTimer;
    bool _wantReconnect{false};
    bool _wasReconnect{false};

    QSet<QObject*> _netsToSync;
    int _numNetsToSync;
    int _progressMinimum{0}, _progressMaximum{-1}, _progressValue{-1};
    QString _progressText;

    bool _resetting{false};

    CoreAccount _account;
    CoreAccountModel* accountModel() const;

    QPointer<QNetworkInformation> _qNetworkInformation;

    friend class CoreConfigWizard;
};

Q_DECLARE_METATYPE(CoreConnection::ConnectionState)

// Inlines
inline int CoreConnection::progressMinimum() const
{
    return _progressMinimum;
}
inline int CoreConnection::progressMaximum() const
{
    return _progressMaximum;
}
inline int CoreConnection::progressValue() const
{
    return _progressValue;
}
inline QString CoreConnection::progressText() const
{
    return _progressText;
}

inline CoreConnection::ConnectionState CoreConnection::state() const
{
    return _state;
}
inline bool CoreConnection::isConnected() const
{
    return state() >= Connected;
}
inline CoreAccount CoreConnection::currentAccount() const
{
    return _account;
}
