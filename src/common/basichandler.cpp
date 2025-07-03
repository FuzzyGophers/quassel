// SPDX-FileCopyrightText: 2005-2025 Quassel Project <devel@quassel-irc.org>
// SPDX-License-Identifier: GPL-2.0-or-later

#include "basichandler.h"

#include <utility>

#include <QDebug>
#include <QMetaMethod>

#include "bufferinfo.h"

BasicHandler::BasicHandler(QObject* parent)
    : QObject(parent)
    , _methodPrefix("handle")
{
}

BasicHandler::BasicHandler(QString methodPrefix, QObject* parent)
    : QObject(parent)
    , _methodPrefix(std::move(methodPrefix))
{
}

QStringList BasicHandler::providesHandlers()
{
    return handlerHash().keys();
}

const QHash<QString, int>& BasicHandler::handlerHash()
{
    if (!_initDone) {
        for (int i = metaObject()->methodOffset(); i < metaObject()->methodCount(); i++) {
            QMetaMethod method = metaObject()->method(i);
            QString methodSignature = QString::fromLatin1(method.methodSignature());
            if (methodSignature.startsWith("defaultHandler")) {
                _defaultHandler = i;
                continue;
            }

            if (!methodSignature.startsWith(_methodPrefix))
                continue;

            QString methodName = methodSignature.section('(', 0, 0);       // chop the parameter list
            QString handlerName = methodName.mid(_methodPrefix.length());  // strip "handle" or other prefix
            _handlerHash[handlerName.toLower()] = i;
        }
        _initDone = true;
    }
    return _handlerHash;
}

void BasicHandler::handle(const QString& member,
                          QGenericArgument val0,
                          QGenericArgument val1,
                          QGenericArgument val2,
                          QGenericArgument val3,
                          QGenericArgument val4,
                          QGenericArgument val5,
                          QGenericArgument val6,
                          QGenericArgument val7,
                          QGenericArgument val8)
{
    if (!_initDone) {
        handlerHash();
    }

    QString handler = member;
    handler[0] = handler[0].toUpper();  // Capitalize first letter to match method name (e.g., "Ping" -> "handleCtcpPing")

    int methodIndex = _handlerHash.value(handler.toLower(), -1);
    if (methodIndex != -1) {
        QMetaMethod method = metaObject()->method(methodIndex);
        method.invoke(this, Qt::DirectConnection, val0, val1, val2, val3, val4, val5, val6, val7, val8);
        return;
    }

    if (_defaultHandler != -1) {
        QMetaMethod defaultMethod = metaObject()->method(_defaultHandler);
        BufferInfo* bufferInfo = static_cast<BufferInfo*>(val0.data());
        QString* text = static_cast<QString*>(val1.data());
        if (bufferInfo && text) {
            defaultMethod.invoke(this, Qt::DirectConnection, Q_ARG(QString, member), Q_ARG(BufferInfo, *bufferInfo), Q_ARG(QString, *text));
        }
        else {
            qWarning() << "Invalid arguments for defaultHandler: bufferInfo=" << bufferInfo << ", text=" << text;
        }
    }
    else {
        qWarning() << QString("No such Handler: %1::%2%3").arg(metaObject()->className(), _methodPrefix, handler);
    }
}
