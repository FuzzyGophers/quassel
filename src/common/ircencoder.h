// SPDX-FileCopyrightText: 2005-2025 Quassel Project <devel@quassel-irc.org>
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

#include "common-export.h"

#include <QByteArray>

#include "irctag.h"

class COMMON_EXPORT IrcEncoder
{
public:
    /**
     * Writes an IRC message
     * @param tags Map of IRCv3 message tags
     * @param prefix Prefix/Source of the message (should be empty)
     * @param cmd
     * @param params
     * @return
     */
    static QByteArray writeMessage(const QHash<IrcTagKey, QString>& tags,
                                   const QByteArray& prefix,
                                   const QString& cmd,
                                   const QList<QByteArray>& params);
private:
    /**
     * Encodes a string as IRCv3 message tag value and appends it to the message
     * @param msg message buffer to append to
     * @param value unencoded tag value
     */
    static void writeTagValue(QByteArray& msg, const QString& value);
    /**
     * Writes IRCv3 message tags to the message buffer
     * @param msg message buffer to append to
     * @param tags map of IRCv3 message tags
     */
    static void writeTags(QByteArray& msg, const QHash<IrcTagKey, QString>& tags);
    /**
     * Writes the prefix/source to the message buffer
     * @param msg message buffer to append to
     * @param prefix prefix/source
     */
    static void writePrefix(QByteArray& msg, const QByteArray& prefix);
    /**
     * Writes the command/verb to the message buffer
     * @param msg message buffer to append to
     * @param cmd command/verb
     */
    static void writeCommand(QByteArray& msg, const QString& cmd);
    /**
     * Writes the command parameters/arguments to the message buffer
     * @param msg message buffer to append to
     * @param params parameters/arguments
     */
    static void writeParams(QByteArray& msg, const QList<QByteArray>& params);
};
