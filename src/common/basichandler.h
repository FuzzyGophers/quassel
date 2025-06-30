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
