// SPDX-FileCopyrightText: 2005-2025 Quassel Project <devel@quassel-irc.org>
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

#include "common-export.h"

#include <QAbstractSocket>
#include <QDataStream>
#include <QPointer>

#include "authhandler.h"
#include "protocol.h"
#include "quassel.h"
#include "signalproxy.h"

class COMMON_EXPORT Peer : public QObject
{
    Q_OBJECT

public:
    explicit Peer(AuthHandler* authHandler, QObject* parent = nullptr);

    virtual QuasselProtocol::Type protocol() const = 0;
    virtual QString description() const = 0;

    virtual SignalProxy* signalProxy() const = 0;
    virtual void setSignalProxy(SignalProxy* proxy) = 0;

    QDateTime connectedSince() const;
    void setConnectedSince(const QDateTime& connectedSince);

    QString buildDate() const;
    void setBuildDate(const QString& buildDate);

    QString clientVersion() const;
    void setClientVersion(const QString& clientVersion);

    bool hasFeature(Quassel::Feature feature) const;
    Quassel::Features features() const;
    void setFeatures(Quassel::Features features);

    int id() const;
    void setId(int id);

    AuthHandler* authHandler() const;

    virtual bool isOpen() const = 0;
    virtual bool isSecure() const = 0;
    virtual bool isLocal() const = 0;

    virtual int lag() const = 0;

    virtual QString address() const = 0;
    virtual quint16 port() const = 0;

public slots:
    /* Handshake messages */
    virtual void dispatch(const QuasselProtocol::RegisterClient&) = 0;
    virtual void dispatch(const QuasselProtocol::ClientDenied&) = 0;
    virtual void dispatch(const QuasselProtocol::ClientRegistered&) = 0;
    virtual void dispatch(const QuasselProtocol::SetupData&) = 0;
    virtual void dispatch(const QuasselProtocol::SetupFailed&) = 0;
    virtual void dispatch(const QuasselProtocol::SetupDone&) = 0;
    virtual void dispatch(const QuasselProtocol::Login&) = 0;
    virtual void dispatch(const QuasselProtocol::LoginFailed&) = 0;
    virtual void dispatch(const QuasselProtocol::LoginSuccess&) = 0;
    virtual void dispatch(const QuasselProtocol::SessionState&) = 0;

    /* Sigproxy messages */
    virtual void dispatch(const QuasselProtocol::SyncMessage&) = 0;
    virtual void dispatch(const QuasselProtocol::RpcCall&) = 0;
    virtual void dispatch(const QuasselProtocol::InitRequest&) = 0;
    virtual void dispatch(const QuasselProtocol::InitData&) = 0;

    virtual void close(const QString& reason = QString()) = 0;

signals:
    void disconnected();
    void secureStateChanged(bool secure = true);
    void lagUpdated(int msecs);

protected:
    template<typename T>
    void handle(const T& protoMessage);

private:
    QPointer<AuthHandler> _authHandler;

    QDateTime _connectedSince;

    QString _buildDate;
    QString _clientVersion;
    Quassel::Features _features;

    int _id = -1;
};

// We need to special-case Peer* in attached signals/slots, so typedef it for the meta type system
using PeerPtr = Peer*;
Q_DECLARE_METATYPE(PeerPtr)

QDataStream& operator<<(QDataStream& out, PeerPtr ptr);
QDataStream& operator>>(QDataStream& in, PeerPtr& ptr);

// Template method needed in the header
template<typename T>
inline void Peer::handle(const T& protoMessage)
{
    switch (protoMessage.handler()) {
    case QuasselProtocol::Handler::SignalProxy:
        if (!signalProxy()) {
            qWarning() << Q_FUNC_INFO << "Cannot handle message without a SignalProxy!";
            return;
        }
        signalProxy()->handle(this, protoMessage);
        break;

    case QuasselProtocol::Handler::AuthHandler:
        if (!authHandler()) {
            qWarning() << Q_FUNC_INFO << "Cannot handle auth messages without an active AuthHandler!";
            return;
        }
        authHandler()->handle(protoMessage);
        break;

    default:
        qWarning() << Q_FUNC_INFO << "Unknown handler for protocol message!";
        return;
    }
}
