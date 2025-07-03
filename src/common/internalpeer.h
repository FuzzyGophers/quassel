// SPDX-FileCopyrightText: 2005-2025 Quassel Project <devel@quassel-irc.org>
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

#include "common-export.h"

#include <QPointer>
#include <QString>

#include "peer.h"
#include "protocol.h"
#include "signalproxy.h"

class COMMON_EXPORT InternalPeer : public Peer
{
    Q_OBJECT

public:
    InternalPeer(QObject* parent = nullptr);
    ~InternalPeer() override;

    QuasselProtocol::Type protocol() const override { return QuasselProtocol::InternalProtocol; }
    QString description() const override;

    QString address() const override;
    quint16 port() const override;

    SignalProxy* signalProxy() const override;
    void setSignalProxy(SignalProxy* proxy) override;

    InternalPeer* peer() const;
    void setPeer(InternalPeer* peer);

    bool isOpen() const override;
    bool isSecure() const override;
    bool isLocal() const override;

    int lag() const override;

    void dispatch(const QuasselProtocol::SyncMessage& msg) override;
    void dispatch(const QuasselProtocol::RpcCall& msg) override;
    void dispatch(const QuasselProtocol::InitRequest& msg) override;
    void dispatch(const QuasselProtocol::InitData& msg) override;

    /* These are not needed for InternalPeer */
    void dispatch(const QuasselProtocol::RegisterClient&) override {}
    void dispatch(const QuasselProtocol::ClientDenied&) override {}
    void dispatch(const QuasselProtocol::ClientRegistered&) override {}
    void dispatch(const QuasselProtocol::SetupData&) override {}
    void dispatch(const QuasselProtocol::SetupFailed&) override {}
    void dispatch(const QuasselProtocol::SetupDone&) override {}
    void dispatch(const QuasselProtocol::Login&) override {}
    void dispatch(const QuasselProtocol::LoginFailed&) override {}
    void dispatch(const QuasselProtocol::LoginSuccess&) override {}
    void dispatch(const QuasselProtocol::SessionState&) override {}

public slots:
    void close(const QString& reason = QString()) override;

signals:
    void dispatchMessage(const QuasselProtocol::SyncMessage& msg);
    void dispatchMessage(const QuasselProtocol::RpcCall& msg);
    void dispatchMessage(const QuasselProtocol::InitRequest& msg);
    void dispatchMessage(const QuasselProtocol::InitData& msg);

private slots:
    void peerDisconnected();

    void handleMessage(const QuasselProtocol::SyncMessage& msg);
    void handleMessage(const QuasselProtocol::RpcCall& msg);
    void handleMessage(const QuasselProtocol::InitRequest& msg);
    void handleMessage(const QuasselProtocol::InitData& msg);

private:
    template<typename T>
    void handle(const T& msg);

private:
    SignalProxy* _proxy{nullptr};
    bool _isOpen{true};
};

Q_DECLARE_METATYPE(QPointer<InternalPeer>)
