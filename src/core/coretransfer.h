// SPDX-FileCopyrightText: 2005-2025 Quassel Project <devel@quassel-irc.org>
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

#include <QPointer>

#include "peer.h"
#include "transfer.h"

class QTcpSocket;

class CoreTransfer : public Transfer
{
    Q_OBJECT

public:
    CoreTransfer(Direction direction,
                 const QString& nick,
                 const QString& fileName,
                 const QHostAddress& address,
                 quint16 port,
                 quint64 size = 0,
                 QObject* parent = nullptr);

    quint64 transferred() const override;

public slots:
    void start();

    // called through sync calls
    void requestAccepted(PeerPtr peer) override;
    void requestRejected(PeerPtr peer) override;

private slots:
    void startReceiving();
    void onDataReceived();
    void onSocketDisconnected();
    void onSocketError(QAbstractSocket::SocketError error);

private:
    void setupConnectionForReceive();
    bool relayData(const QByteArray& data, bool requireChunkSize);
    void cleanUp() override;

    QPointer<Peer> _peer;
    QTcpSocket* _socket;
    quint64 _pos;
    QByteArray _buffer;
    bool _reading;
};
