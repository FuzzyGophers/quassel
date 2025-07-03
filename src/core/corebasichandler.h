// SPDX-FileCopyrightText: 2005-2025 Quassel Project <devel@quassel-irc.org>
// SPDX-License-Identifier: GPL-2.0-or-later

#ifndef COREBASICHANDLER_H
#define COREBASICHANDLER_H

#include <QString>
#include <QStringList>

#include "basichandler.h"
#include "corenetwork.h"
#include "message.h"

class CoreSession;

class CoreBasicHandler : public BasicHandler
{
    Q_OBJECT

public:
    CoreBasicHandler(CoreNetwork* parent = nullptr);

    QString serverDecode(const QByteArray& string);
    QStringList serverDecode(const QList<QByteArray>& stringlist);
    QString channelDecode(const QString& bufferName, const QByteArray& string);
    QStringList channelDecode(const QString& bufferName, const QList<QByteArray>& stringlist);
    QString userDecode(const QString& userNick, const QByteArray& string);
    QStringList userDecode(const QString& userNick, const QList<QByteArray>& stringlist);

    QByteArray serverEncode(const QString& string);
    QList<QByteArray> serverEncode(const QStringList& stringlist);
    QByteArray channelEncode(const QString& bufferName, const QString& string);
    QList<QByteArray> channelEncode(const QString& bufferName, const QStringList& stringlist);
    QByteArray userEncode(const QString& userNick, const QString& string);
    QList<QByteArray> userEncode(const QString& userNick, const QStringList& stringlist);

signals:
    void displayMsg(const NetworkInternalMessage& msg);

    /**
     * Sends the raw (encoded) line, adding to the queue if needed, optionally with higher priority.
     *
     * @see CoreNetwork::putRawLine()
     */
    void putRawLine(const QByteArray& msg, bool prepend = false);

    /**
     * Sends the command with encoded parameters, with optional prefix or high priority.
     *
     * @see CoreNetwork::putCmd(const QString &cmd, const QList<QByteArray> &params, const QByteArray &prefix = QByteArray(), const
     * QHash<IrcTagKey, QString>& tags = {}, bool prepend = false)
     */
    void putCmd(const QString& cmd,
                const QList<QByteArray>& params,
                const QByteArray& prefix = {},
                const QHash<IrcTagKey, QString>& tags = {},
                bool prepend = false);

    /**
     * Sends the command for each set of encoded parameters, with optional prefix or high priority.
     *
     * @see CoreNetwork::putCmd(const QString &cmd, const QList<QList<QByteArray>> &params, const QByteArray &prefix = QByteArray(), const
     * QHash<IrcTagKey, QString>& tags = {}, bool prepend = false)
     */
    void putCmd(const QString& cmd,
                const QList<QList<QByteArray>>& params,
                const QByteArray& prefix = {},
                const QHash<IrcTagKey, QString>& tags = {},
                bool prepend = false);

protected:
    /**
     * Sends the command with one parameter, with optional prefix or high priority.
     *
     * @param[in] cmd      Command to send, ignoring capitalization
     * @param[in] param    Parameter for the command, encoded within a QByteArray
     * @param[in] prefix   Optional command prefix
     * @param[in] tags     Optional command tags
     * @param[in] prepend
     * @parmblock
     * If true, the command is prepended into the start of the queue, otherwise, it's appended to
     * the end.  This should be used sparingly, for if either the core or the IRC server cannot
     * maintain PING/PONG replies, the other side will close the connection.
     * @endparmblock
     */
    void putCmd(const QString& cmd,
                const QByteArray& param,
                const QByteArray& prefix = QByteArray(),
                const QHash<IrcTagKey, QString>& tags = {},
                bool prepend = false);

    inline CoreNetwork* network() const { return _network; }
    inline CoreSession* coreSession() const { return _network->coreSession(); }

    BufferInfo::Type typeByTarget(const QString& target) const;

private:
    CoreNetwork* _network;
};

#endif
