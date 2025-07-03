// SPDX-FileCopyrightText: 2005-2025 Quassel Project <devel@quassel-irc.org>
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

#include "common-export.h"

#include <QDateTime>

#include "compressor.h"
#include "peer.h"
#include "protocol.h"
#include "proxyline.h"
#include "signalproxy.h"

class QTimer;

class AuthHandler;

class COMMON_EXPORT RemotePeer : public Peer
{
    Q_OBJECT

public:
    // import the virtuals from the baseclass
    using Peer::dispatch;
    using Peer::handle;

    RemotePeer(AuthHandler* authHandler, QTcpSocket* socket, Compressor::CompressionLevel level, QObject* parent = nullptr);

    void setSignalProxy(SignalProxy* proxy) override;

    void setProxyLine(ProxyLine proxyLine);

    virtual QString protocolName() const = 0;
    QString description() const override;
    virtual quint16 enabledFeatures() const { return 0; }

    QString address() const override;
    QHostAddress hostAddress() const;
    quint16 port() const override;

    bool isOpen() const override;
    bool isSecure() const override;
    bool isLocal() const override;

    int lag() const override;

    bool compressionEnabled() const;
    void setCompressionEnabled(bool enabled);

    QTcpSocket* socket() const;

public slots:
    void close(const QString& reason = QString()) override;

signals:
    void transferProgress(int current, int max);
    void socketError(QAbstractSocket::SocketError error, const QString& errorString);
    void statusMessage(const QString& msg);

    // Only used by LegacyPeer
    void protocolVersionMismatch(int actual, int expected);

protected:
    SignalProxy* signalProxy() const override;

    void writeMessage(const QByteArray& msg);
    virtual void processMessage(const QByteArray& msg) = 0;

    // These protocol messages get handled internally and won't reach SignalProxy
    void handle(const QuasselProtocol::HeartBeat& heartBeat);
    void handle(const QuasselProtocol::HeartBeatReply& heartBeatReply);
    virtual void dispatch(const QuasselProtocol::HeartBeat& msg) = 0;
    virtual void dispatch(const QuasselProtocol::HeartBeatReply& msg) = 0;

protected slots:
    virtual void onSocketStateChanged(QAbstractSocket::SocketState state);
    virtual void onSocketError(QAbstractSocket::SocketError error);

private slots:
    void onReadyRead();
    void onCompressionError(Compressor::Error error);

    void sendHeartBeat();
    void changeHeartBeatInterval(int secs);

private:
    bool readMessage(QByteArray& msg);

private:
    QTcpSocket* _socket;
    Compressor* _compressor;
    SignalProxy* _signalProxy;
    ProxyLine _proxyLine;
    bool _useProxyLine;
    QTimer* _heartBeatTimer;
    int _heartBeatCount;
    int _lag;
    quint32 _msgSize;
};
