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
