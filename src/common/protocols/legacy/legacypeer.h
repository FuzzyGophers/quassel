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

#ifndef LEGACYPEER_H
#define LEGACYPEER_H

#include "../../remotepeer.h"

class LegacyPeer : public RemotePeer
{
    Q_OBJECT

public:
    enum RequestType
    {
        Sync = 1,
        RpcCall,
        InitRequest,
        InitData,
        HeartBeat,
        HeartBeatReply
    };

    LegacyPeer(AuthHandler* authHandler, QTcpSocket* socket, Compressor::CompressionLevel level, QObject* parent = nullptr);

    QuasselProtocol::Type protocol() const override { return QuasselProtocol::LegacyProtocol; }
    QString protocolName() const override { return "the legacy protocol"; }

    void setSignalProxy(SignalProxy* proxy) override;

    void dispatch(const QuasselProtocol::RegisterClient& msg) override;
    void dispatch(const QuasselProtocol::ClientDenied& msg) override;
    void dispatch(const QuasselProtocol::ClientRegistered& msg) override;
    void dispatch(const QuasselProtocol::SetupData& msg) override;
    void dispatch(const QuasselProtocol::SetupFailed& msg) override;
    void dispatch(const QuasselProtocol::SetupDone& msg) override;
    void dispatch(const QuasselProtocol::Login& msg) override;
    void dispatch(const QuasselProtocol::LoginFailed& msg) override;
    void dispatch(const QuasselProtocol::LoginSuccess& msg) override;
    void dispatch(const QuasselProtocol::SessionState& msg) override;

    void dispatch(const QuasselProtocol::SyncMessage& msg) override;
    void dispatch(const QuasselProtocol::RpcCall& msg) override;
    void dispatch(const QuasselProtocol::InitRequest& msg) override;
    void dispatch(const QuasselProtocol::InitData& msg) override;

    void dispatch(const QuasselProtocol::HeartBeat& msg) override;
    void dispatch(const QuasselProtocol::HeartBeatReply& msg) override;

signals:
    void protocolError(const QString& errorString);

private:
    using RemotePeer::writeMessage;
    void writeMessage(const QVariant& item);
    void processMessage(const QByteArray& msg) override;

    void handleHandshakeMessage(const QVariant& msg);
    void handlePackedFunc(const QVariant& packedFunc);
    void dispatchPackedFunc(const QVariantList& packedFunc);

    void toLegacyIrcUsersAndChannels(QVariantMap& initData);
    void fromLegacyIrcUsersAndChannels(QVariantMap& initData);

    bool _useCompression;
};

#endif
