// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

#include <QHash>
#include <QObject>
#include <QString>
#include <QTcpServer>

#include "coreidentity.h"

class MetricsServer : public QObject
{
    Q_OBJECT

public:
    explicit MetricsServer(QObject* parent = nullptr);

    bool startListening();
    void stopListening(const QString& msg);

    void addLoginAttempt(UserId user, bool successful);
    void addLoginAttempt(const QString& user, bool successful);

    void addSession(UserId user, const QString& name);
    void removeSession(UserId user);

    void addClient(UserId user);
    void removeClient(UserId user);

    void addNetwork(UserId user);
    void removeNetwork(UserId user);

    void transmitDataNetwork(UserId user, uint64_t size);
    void receiveDataNetwork(UserId user, uint64_t size);

    void messageQueue(UserId user, uint64_t size);

    void setCertificateExpires(QDateTime expires);

private slots:
    void incomingConnection();
    void respond();

private:
    QTcpServer _server, _v6server;

    QHash<UserId, uint64_t> _loginAttempts{};
    QHash<UserId, uint64_t> _successfulLogins{};

    QHash<UserId, QString> _sessions{};

    QHash<UserId, int32_t> _clientSessions{};
    QHash<UserId, int32_t> _networkSessions{};

    QHash<UserId, uint64_t> _networkDataTransmit{};
    QHash<UserId, uint64_t> _networkDataReceive{};

    QHash<UserId, uint64_t> _messageQueue{};

    QDateTime _certificateExpires{};
};
