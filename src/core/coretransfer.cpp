// SPDX-FileCopyrightText: 2005-2025 Quassel Project <devel@quassel-irc.org>
// SPDX-License-Identifier: GPL-2.0-or-later

#include "coretransfer.h"

#include <QCoreApplication>
#include <QTcpSocket>
#include <QtEndian>

#include "util.h"

const qint64 chunkSize = 16 * 1024;

CoreTransfer::CoreTransfer(Direction direction,
                           const QString& nick,
                           const QString& fileName,
                           const QHostAddress& address,
                           quint16 port,
                           quint64 fileSize,
                           QObject* parent)
    : Transfer(direction, nick, fileName, address, port, fileSize, parent)
    , _socket(nullptr)
    , _pos(0)
    , _reading(false)
{
}

quint64 CoreTransfer::transferred() const
{
    return _pos;
}

void CoreTransfer::cleanUp()
{
    if (_socket) {
        _socket->close();
        _socket->deleteLater();
        _socket = nullptr;
    }

    _buffer.clear();
    _reading = false;
}

void CoreTransfer::onSocketDisconnected()
{
    if (status() == Status::Connecting || status() == Status::Transferring) {
        setError(tr("Socket closed while still transferring!"));
    }
    else
        cleanUp();
}

void CoreTransfer::onSocketError(QAbstractSocket::SocketError error)
{
    Q_UNUSED(error)

    if (status() == Status::Connecting || status() == Status::Transferring) {
        setError(tr("DCC connection error: %1").arg(_socket->errorString()));
    }
}

void CoreTransfer::requestAccepted(PeerPtr peer)
{
    if (_peer || !peer || status() != Status::New)
        return;  // transfer was already accepted

    _peer = peer;
    setStatus(Status::Pending);

    emit accepted(peer);

    // FIXME temporary until we have queueing
    start();
}

void CoreTransfer::requestRejected(PeerPtr peer)
{
    if (_peer || status() != Status::New)
        return;

    _peer = peer;
    setStatus(Status::Rejected);

    emit rejected(peer);
}

void CoreTransfer::start()
{
    if (!_peer || status() != Status::Pending || direction() != Direction::Receive)
        return;

    setupConnectionForReceive();
}

void CoreTransfer::setupConnectionForReceive()
{
    if (port() == 0) {
        setError(tr("Reverse DCC not supported yet!"));
        return;
    }

    setStatus(Status::Connecting);

    _socket = new QTcpSocket(this);
    connect(_socket, &QAbstractSocket::connected, this, &CoreTransfer::startReceiving);
    connect(_socket, &QAbstractSocket::disconnected, this, &CoreTransfer::onSocketDisconnected);
    connect(_socket, &QAbstractSocket::errorOccurred, this, &CoreTransfer::onSocketError);
    connect(_socket, &QIODevice::readyRead, this, &CoreTransfer::onDataReceived);

    _socket->connectToHost(address(), port());
}

void CoreTransfer::startReceiving()
{
    setStatus(Status::Transferring);
}

void CoreTransfer::onDataReceived()
{
    if (_reading)  // since we're spinning the event loop, we may get another readyRead() and thus reentrancy
        return;
    _reading = true;

    while (_socket->bytesAvailable()) {
        QByteArray data = _socket->read(chunkSize);
        _pos += data.size();
        emit transferredChanged(transferred());
        if (!relayData(data, true))
            return;

        QCoreApplication::processEvents();  // don't block the rest of the core/client communication
        if (!_socket)                       // just in case something happened during spinning the event loop that killed our socket
            return;
    }

    // Send ack to sender. The DCC protocol only specifies 32 bit values, but modern clients (i.e. those who can send files
    // larger than 4 GB) will ignore this anyway...
    quint32 ack = qToBigEndian((quint32)_pos);  // qDebug() << Q_FUNC_INFO << _pos;
    _socket->write((char*)&ack, 4);

    if (_pos > fileSize()) {
        qWarning() << "DCC Receive: Got more data than expected!";
        setError(tr("DCC Receive: Got more data than expected!"));
    }
    else if (_pos == fileSize()) {
        qDebug() << "DCC Receive: Transfer finished";
        if (relayData(QByteArray(), false))  // empty buffer
            setStatus(Status::Completed);
    }

    _reading = false;
}

bool CoreTransfer::relayData(const QByteArray& data, bool requireChunkSize)
{
    // safeguard against a disconnecting quasselclient
    if (!_peer) {
        setError(tr("DCC Receive: Quassel Client disconnected during transfer!"));
        return false;
    }
    _buffer.append(data);

    // we only want to send data to the client once we have reached the chunksize
    if (_buffer.size() > 0 && (_buffer.size() >= chunkSize || !requireChunkSize)) {
        Peer* p = _peer.data();
        SYNC_OTHER(dataReceived, ARG(p), ARG(_buffer));
        _buffer.clear();
    }

    return true;
}
