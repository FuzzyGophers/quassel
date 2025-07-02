// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

#include <list>

#include <QHash>
#include <QObject>
#include <QPointer>
#include <QString>
#include <QTcpServer>
#include <QTcpSocket>

#include "coreidentity.h"

struct Request
{
    QPointer<QTcpSocket> socket;
    uint16_t localPort;
    uint16_t remotePort;
    QString query;
    qint64 transactionId;
    qint64 requestId;

    friend bool operator==(const Request& a, const Request& b);

    void respondSuccess(const QString& user);
    void respondError(const QString& error);

    const static int DISCONNECTION_TIMEOUT = 500;
};

class IdentServer : public QObject
{
    Q_OBJECT

public:
    IdentServer(QObject* parent = nullptr);

    bool startListening();
    void stopListening(const QString& msg);
    qint64 addWaitingSocket();

public slots:
    void addSocket(const CoreIdentity* identity,
                   const QHostAddress& localAddress,
                   quint16 localPort,
                   const QHostAddress& peerAddress,
                   quint16 peerPort,
                   qint64 socketId);
    void removeSocket(const CoreIdentity* identity,
                      const QHostAddress& localAddress,
                      quint16 localPort,
                      const QHostAddress& peerAddress,
                      quint16 peerPort,
                      qint64 socketId);

private slots:
    void incomingConnection();
    void respond();

private:
    bool responseAvailable(Request request) const;

    qint64 lowestSocketId() const;

    void processWaiting(qint64 socketId);

    void removeWaitingSocket(qint64 socketId);

    QTcpServer _server, _v6server;

    QHash<uint16_t, QString> _connections;
    std::list<Request> _requestQueue;
    std::list<qint64> _waiting;
    qint64 _socketId{0};
    qint64 _requestId{0};
};
