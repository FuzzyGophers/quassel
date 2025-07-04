// SPDX-FileCopyrightText: 2005-2025 Quassel Project <devel@quassel-irc.org>
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

#include <utility>

#include "corebasichandler.h"
#include "corenetwork.h"

class Cipher;
class Server;

class CoreUserInputHandler : public CoreBasicHandler
{
    Q_OBJECT

public:
    CoreUserInputHandler(CoreNetwork* parent = nullptr);
    inline CoreNetwork* coreNetwork() const { return qobject_cast<CoreNetwork*>(parent()); }

    void handleUserInput(const BufferInfo& bufferInfo, const QString& text);
    int lastParamOverrun(const QString& cmd, const QList<QByteArray>& params);

public slots:
    /**
     * Handle the away command, marking as away or unaway
     *
     * Applies to the current network unless text begins with "-all".
     *
     * @param[in] bufferInfo      Currently active buffer
     * @param[in] text            Away message, or blank to set unaway
     * @param[in] skipFormatting  If true, skip timestamp formatting codes (e.g. if already done)
     */
    void handleAway(const BufferInfo& bufferInfo, const QString& text, const bool skipFormatting = false);
    void handleBan(const BufferInfo& bufferInfo, const QString& text);
    void handleUnban(const BufferInfo& bufferInfo, const QString& text);
    void handleCtcp(const BufferInfo& bufferInfo, const QString& text);
    void handleDelkey(const BufferInfo& bufferInfo, const QString& text);
    void handleDeop(const BufferInfo& bufferInfo, const QString& nicks);
    void handleDehalfop(const BufferInfo& bufferInfo, const QString& nicks);
    void handleDevoice(const BufferInfo& bufferInfo, const QString& nicks);
    void handleInvite(const BufferInfo& bufferInfo, const QString& text);
    void handleJoin(const BufferInfo& bufferInfo, const QString& text);
    void handleKeyx(const BufferInfo& bufferInfo, const QString& text);
    void handleKick(const BufferInfo& bufferInfo, const QString& text);
    void handleKill(const BufferInfo& bufferInfo, const QString& text);
    void handleList(const BufferInfo& bufferInfo, const QString& text);
    void handleMe(const BufferInfo& bufferInfo, const QString& text);
    void handleMode(const BufferInfo& bufferInfo, const QString& text);
    void handleMsg(const BufferInfo& bufferInfo, const QString& text);
    void handleNick(const BufferInfo& bufferInfo, const QString& text);
    void handleNotice(const BufferInfo& bufferInfo, const QString& text);
    void handleOper(const BufferInfo& bufferInfo, const QString& text);
    void handleOp(const BufferInfo& bufferInfo, const QString& nicks);
    void handleHalfop(const BufferInfo& bufferInfo, const QString& nicks);
    void handlePart(const BufferInfo& bufferInfo, const QString& text);
    void handlePing(const BufferInfo& bufferInfo, const QString& text);
    void handlePrint(const BufferInfo& bufferInfo, const QString& text);
    void handleQuery(const BufferInfo& bufferInfo, const QString& text);
    void handleQuit(const BufferInfo& bufferInfo, const QString& text);
    void handleQuote(const BufferInfo& bufferInfo, const QString& text);
    void handleSay(const BufferInfo& bufferInfo, const QString& text);
    void handleSetkey(const BufferInfo& bufferInfo, const QString& text);
    /**
     * Handle the setname command, setting the user's realname
     *
     * @param bufferInfo  Currently active buffer
     * @param text        New realname
     */
    void handleSetname(const BufferInfo& bufferInfo, const QString& text);
    void handleShowkey(const BufferInfo& bufferInfo, const QString& text);
    void handleTopic(const BufferInfo& bufferInfo, const QString& text);
    void handleVoice(const BufferInfo& bufferInfo, const QString& text);
    void handleWait(const BufferInfo& bufferInfo, const QString& text);
    void handleWho(const BufferInfo& bufferInfo, const QString& text);
    void handleWhois(const BufferInfo& bufferInfo, const QString& text);
    void handleWhowas(const BufferInfo& bufferInfo, const QString& text);

    void defaultHandler(QString cmd, const BufferInfo& bufferInfo, const QString& text);

    /**
     * Send a QUIT to the IRC server, optionally skipping the command queue.
     *
     * @param reason          Reason for quitting, often displayed to other IRC clients
     * @param forceImmediate  Immediately quit, skipping queue of other commands
     */
    void issueQuit(const QString& reason, bool forceImmediate = false);

    /**
     * Issues the away command, marking as away or unaway on the current network
     *
     * @param[in] msg             Away message, or blank to set unaway
     * @param[in] autoCheck       If true, always set away, defaulting to the identity away message
     * @param[in] skipFormatting  If true, skip timestamp formatting codes (e.g. if already done)
     */
    void issueAway(const QString& msg, bool autoCheck = true, const bool skipFormatting = false);

protected:
    void timerEvent(QTimerEvent* event) override;

private:
    void doMode(const BufferInfo& bufferInfo, const QChar& addOrRemove, const QChar& mode, const QString& nickList);
    void banOrUnban(const BufferInfo& bufferInfo, const QString& text, bool ban);
    void putPrivmsg(const QString& target,
                    const QString& message,
                    std::function<QByteArray(const QString&, const QString&)> encodeFunc,
                    Cipher* cipher = nullptr);

#ifdef HAVE_QCA2
    QByteArray encrypt(const QString& target, const QByteArray& message, bool* didEncrypt = nullptr) const;
#endif

    struct Command
    {
        BufferInfo bufferInfo;
        QString command;
        Command(BufferInfo info, QString command)
            : bufferInfo(std::move(info))
            , command(std::move(command))
        {
        }
        Command() = default;
    };

    QHash<int, Command> _delayedCommands;
};
