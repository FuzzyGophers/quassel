/***************************************************************************
 *   Copyright (C) 2005-2022 by the Quassel Project                        *
 *   devel@quassel-irc.org                                                 *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) version 3.                                           *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   You should have received a copy of the GNU General Public License     *
 *   along with this program; if not, write to the                         *
 *   Free Software Foundation, Inc.,                                       *
 *   51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.         *
 ***************************************************************************/

#pragma once

#include "common-export.h"

#include <QSslSocket>

#include "protocol.h"

class Peer;

class COMMON_EXPORT AuthHandler : public QObject
{
    Q_OBJECT

public:
    AuthHandler(QObject* parent = nullptr);

    QSslSocket* socket() const;

    virtual bool isLocal() const;

    virtual void handle(const QuasselProtocol::RegisterClient&) { invalidMessage(); }
    virtual void handle(const QuasselProtocol::ClientDenied&) { invalidMessage(); }
    virtual void handle(const QuasselProtocol::ClientRegistered&) { invalidMessage(); }
    virtual void handle(const QuasselProtocol::SetupData&) { invalidMessage(); }
    virtual void handle(const QuasselProtocol::SetupFailed&) { invalidMessage(); }
    virtual void handle(const QuasselProtocol::SetupDone&) { invalidMessage(); }
    virtual void handle(const QuasselProtocol::Login&) { invalidMessage(); }
    virtual void handle(const QuasselProtocol::LoginFailed&) { invalidMessage(); }
    virtual void handle(const QuasselProtocol::LoginSuccess&) { invalidMessage(); }
    virtual void handle(const QuasselProtocol::SessionState&) { invalidMessage(); }

    // fallback for unknown types, will trigger an error
    template<class T>
    void handle(const T&)
    {
        invalidMessage();
    }

public slots:
    void close();

signals:
    void disconnected();
    void socketError(QAbstractSocket::SocketError error, const QString& errorString);

protected:
    void setSocket(QSslSocket* socket);

protected slots:
    virtual void onSocketError(QAbstractSocket::SocketError error);
    virtual void onSocketDisconnected();

private:
    void invalidMessage();

    QSslSocket* _socket{nullptr};  // FIXME: should be a QSharedPointer? -> premature disconnect before the peer has taken over
    bool _disconnectedSent{false};
};
