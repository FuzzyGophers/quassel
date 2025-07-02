// SPDX-License-Identifier: GPL-2.0-or-later

#include "authhandler.h"

#include <QHostAddress>

#include "util.h"

AuthHandler::AuthHandler(QObject* parent)
    : QObject(parent)
{}

QSslSocket* AuthHandler::socket() const
{
    return _socket;
}

void AuthHandler::setSocket(QSslSocket* socket)
{
    _socket = socket;
    connect(socket, &QAbstractSocket::errorOccurred, this, &AuthHandler::onSocketError);
    connect(socket, &QAbstractSocket::disconnected, this, &AuthHandler::onSocketDisconnected);
}

bool AuthHandler::isLocal() const
{
    if (socket()) {
        if (socket()->peerAddress() == QHostAddress::LocalHost || socket()->peerAddress() == QHostAddress::LocalHostIPv6)
            return true;
    }
    return false;
}

// Some errors (e.g. connection refused) don't trigger a disconnected() from the socket, so send this explicitly
// (but make sure it's only sent once!)
void AuthHandler::onSocketError(QAbstractSocket::SocketError error)
{
    emit socketError(error, _socket->errorString());

    if (!socket()->isOpen() || !socket()->isValid()) {
        if (!_disconnectedSent) {
            _disconnectedSent = true;
            emit disconnected();
        }
    }
}

void AuthHandler::onSocketDisconnected()
{
    if (!_disconnectedSent) {
        _disconnectedSent = true;
        emit disconnected();
    }
}

void AuthHandler::invalidMessage()
{
    qWarning() << Q_FUNC_INFO << "No handler for message!";
}

void AuthHandler::close()
{
    if (_socket && _socket->isOpen())
        _socket->close();
}
