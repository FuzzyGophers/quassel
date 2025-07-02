// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

#include "common-export.h"

#include <QGenericArgument>
#include <QHash>
#include <QObject>
#include <QString>
#include <QStringList>

class COMMON_EXPORT BasicHandler : public QObject
{
    Q_OBJECT

public:
    BasicHandler(QObject* parent = nullptr);
    BasicHandler(QString methodPrefix, QObject* parent = nullptr);

    /**
     * Returns a list of handler method names (without the method prefix) supported by this class.
     * For example, if the prefix is "handleCtcp", returns names like "Ping", "Version", etc.
     */
    QStringList providesHandlers();

protected:
    /**
     * Dynamically invokes a handler method based on the given member name.
     * Tries to call a method named "<methodPrefix><member>" (e.g., "handleCtcpPing") with the provided arguments.
     * If no such method exists, falls back to defaultHandler(QString, T) if available.
     *
     * @param member The handler name (e.g., "Ping" for "handleCtcpPing").
     * @param val0 First argument, typically a pointer to an event object (e.g., CtcpEvent*).
     * @param val1-val8 Additional arguments (unused in most cases).
     */
    virtual void handle(const QString& member,
                        QGenericArgument val0 = QGenericArgument(nullptr),
                        QGenericArgument val1 = QGenericArgument(nullptr),
                        QGenericArgument val2 = QGenericArgument(nullptr),
                        QGenericArgument val3 = QGenericArgument(nullptr),
                        QGenericArgument val4 = QGenericArgument(nullptr),
                        QGenericArgument val5 = QGenericArgument(nullptr),
                        QGenericArgument val6 = QGenericArgument(nullptr),
                        QGenericArgument val7 = QGenericArgument(nullptr),
                        QGenericArgument val8 = QGenericArgument(nullptr));

private:
    /**
     * Returns the hash mapping handler names to method indices.
     */
    const QHash<QString, int>& handlerHash();
    QHash<QString, int> _handlerHash;
    int _defaultHandler{-1};
    bool _initDone{false};
    QString _methodPrefix;
};
