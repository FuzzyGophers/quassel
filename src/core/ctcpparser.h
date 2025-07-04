// SPDX-FileCopyrightText: 2005-2025 Quassel Project <devel@quassel-irc.org>
// SPDX-License-Identifier: GPL-2.0-or-later

#ifndef CTCPPARSER_H
#define CTCPPARSER_H

#include <utility>

#include <QUuid>

#include "corenetwork.h"
#include "ctcpevent.h"
#include "eventmanager.h"
#include "ircevent.h"

class CoreSession;
class CtcpEvent;

class CtcpParser : public QObject
{
    Q_OBJECT

public:
    CtcpParser(CoreSession* coreSession, QObject* parent = nullptr);

    inline CoreSession* coreSession() const { return _coreSession; }

    void query(CoreNetwork* network, const QString& bufname, const QString& ctcpTag, const QString& message);
    void reply(CoreNetwork* network, const QString& bufname, const QString& ctcpTag, const QString& message);

    Q_INVOKABLE void processIrcEventRawNotice(IrcEventRawMessage* event);
    Q_INVOKABLE void processIrcEventRawPrivmsg(IrcEventRawMessage* event);

    Q_INVOKABLE void sendCtcpEvent(CtcpEvent* event);

signals:
    void newEvent(Event* event);

protected:
    inline CoreNetwork* coreNetwork(NetworkEvent* e) const { return qobject_cast<CoreNetwork*>(e->network()); }

    // FIXME duplicates functionality in EventStringifier, maybe want to put that in something common
    //! Creates and sends a MessageEvent
    void displayMsg(NetworkEvent* event,
                    Message::Type msgType,
                    QString msg,
                    QString sender = {},
                    QString target = {},
                    Message::Flags msgFlags = Message::None);

    void parse(IrcEventRawMessage* event, Message::Type msgType);
    void parseSimple(IrcEventRawMessage* e,
                     Message::Type messagetype,
                     const QByteArray& dequotedMessage,
                     CtcpEvent::CtcpType ctcptype,
                     Message::Flags flags);
    void parseStandard(IrcEventRawMessage* e,
                       Message::Type messagetype,
                       const QByteArray& dequotedMessage,
                       CtcpEvent::CtcpType ctcptype,
                       Message::Flags flags);

    QByteArray lowLevelQuote(const QByteArray&);
    QByteArray lowLevelDequote(const QByteArray&);
    QByteArray xdelimQuote(const QByteArray&);
    QByteArray xdelimDequote(const QByteArray&);

    QByteArray pack(const QByteArray& ctcpTag, const QByteArray& message);
    void packedReply(CoreNetwork* network, const QString& bufname, const QList<QByteArray>& replies);

private slots:
    void setStandardCtcp(bool enabled);

private:
    inline QString targetDecode(IrcEventRawMessage* e, const QByteArray& msg) { return coreNetwork(e)->userDecode(e->target(), msg); }

    CoreSession* _coreSession;

    struct CtcpReply
    {
        CoreNetwork* network{nullptr};
        QString bufferName;
        QList<QByteArray> replies;

        CtcpReply() = default;
        CtcpReply(CoreNetwork* net, QString buf)
            : network(net)
            , bufferName(std::move(buf))
        {
        }
    };

    QHash<QUuid, CtcpReply> _replies;

    QHash<QByteArray, QByteArray> _ctcpMDequoteHash;
    QHash<QByteArray, QByteArray> _ctcpXDelimDequoteHash;
};

#endif
