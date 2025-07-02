// SPDX-License-Identifier: GPL-2.0-or-later

#include <utility>

#include <QDataStream>

#include "message.h"
#include "peer.h"
#include "signalproxy.h"
#include "util.h"

Message::Message(BufferInfo bufferInfo,
                 Type type,
                 QString contents,
                 QString sender,
                 QString senderPrefixes,
                 QString realName,
                 QString avatarUrl,
                 Flags flags)
    : _timestamp(QDateTime::currentDateTime().toUTC())
    , _bufferInfo(std::move(bufferInfo))
    , _contents(std::move(contents))
    , _sender(std::move(sender))
    , _senderPrefixes(std::move(senderPrefixes))
    , _realName(std::move(realName))
    , _avatarUrl(std::move(avatarUrl))
    , _type(type)
    , _flags(flags)
{}

Message::Message(QDateTime ts,
                 BufferInfo bufferInfo,
                 Type type,
                 QString contents,
                 QString sender,
                 QString senderPrefixes,
                 QString realName,
                 QString avatarUrl,
                 Flags flags)
    : _timestamp(std::move(ts))
    , _bufferInfo(std::move(bufferInfo))
    , _contents(std::move(contents))
    , _sender(std::move(sender))
    , _senderPrefixes(std::move(senderPrefixes))
    , _realName(std::move(realName))
    , _avatarUrl(std::move(avatarUrl))
    , _type(type)
    , _flags(flags)
{}

QDataStream& operator<<(QDataStream& out, const Message& msg)
{
    Q_ASSERT(SignalProxy::current());
    Q_ASSERT(SignalProxy::current()->targetPeer());

    out << msg.msgId();

    if (SignalProxy::current()->targetPeer()->hasFeature(Quassel::Feature::LongTime)) {
        // toMSecsSinceEpoch returns a qint64
        out << (qint64)msg.timestamp().toMSecsSinceEpoch();
    }
    else {
        // toSecsSinceEpoch returns a qint64, but we cast to quint32 for backward compatibility
        out << (quint32)msg.timestamp().toSecsSinceEpoch();
    }

    out << (quint32)msg.type()
        << (quint8)msg.flags()
        << msg.bufferInfo()
        << msg.sender().toUtf8();

    if (SignalProxy::current()->targetPeer()->hasFeature(Quassel::Feature::SenderPrefixes))
        out << msg.senderPrefixes().toUtf8();

    if (SignalProxy::current()->targetPeer()->hasFeature(Quassel::Feature::RichMessages)) {
        out << msg.realName().toUtf8();
        out << msg.avatarUrl().toUtf8();
    }

    out << msg.contents().toUtf8();
    return out;
}

QDataStream& operator>>(QDataStream& in, Message& msg)
{
    Q_ASSERT(SignalProxy::current());
    Q_ASSERT(SignalProxy::current()->sourcePeer());

    in >> msg._msgId;

    if (SignalProxy::current()->sourcePeer()->hasFeature(Quassel::Feature::LongTime)) {
        // timestamp is a qint64
        qint64 timeStamp;
        in >> timeStamp;
        msg._timestamp = QDateTime::fromMSecsSinceEpoch(timeStamp);
    }
    else {
        quint32 timeStamp;
        in >> timeStamp;
        msg._timestamp = QDateTime::fromSecsSinceEpoch(timeStamp);
    }

    quint32 type;
    in >> type;
    msg._type = Message::Type(type);

    quint8 flags;
    in >> flags;
    msg._flags = Message::Flags(flags);

    in >> msg._bufferInfo;

    QByteArray sender;
    in >> sender;
    msg._sender = QString::fromUtf8(sender);

    QByteArray senderPrefixes;
    if (SignalProxy::current()->sourcePeer()->hasFeature(Quassel::Feature::SenderPrefixes))
        in >> senderPrefixes;
    msg._senderPrefixes = QString::fromUtf8(senderPrefixes);

    QByteArray realName;
    QByteArray avatarUrl;
    if (SignalProxy::current()->sourcePeer()->hasFeature(Quassel::Feature::RichMessages)) {
        in >> realName;
        in >> avatarUrl;
    }
    msg._realName = QString::fromUtf8(realName);
    msg._avatarUrl = QString::fromUtf8(avatarUrl);

    QByteArray contents;
    in >> contents;
    msg._contents = QString::fromUtf8(contents);

    return in;
}

QDebug operator<<(QDebug dbg, const Message& msg)
{
    dbg.nospace() << qPrintable(QString("Message(MsgId:")) << msg.msgId()
                  << qPrintable(QString(",")) << msg.timestamp()
                  << qPrintable(QString(", Type:")) << msg.type()
                  << qPrintable(QString(", RealName:")) << msg.realName()
                  << qPrintable(QString(", AvatarURL:")) << msg.avatarUrl()
                  << qPrintable(QString(", Flags:")) << msg.flags()
                  << qPrintable(QString(")"))
                  << msg.senderPrefixes() << msg.sender() << ":"
                  << msg.contents();
    return dbg;
}
