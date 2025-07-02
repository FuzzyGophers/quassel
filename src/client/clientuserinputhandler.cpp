// SPDX-License-Identifier: GPL-2.0-or-later

#include "clientuserinputhandler.h"

#include <QDateTime>

#include "bufferinfo.h"
#include "buffermodel.h"
#include "client.h"
#include "clientaliasmanager.h"
#include "clientbufferviewconfig.h"
#include "clientbufferviewmanager.h"
#include "clientignorelistmanager.h"
#include "clientsettings.h"
#include "execwrapper.h"
#include "ignorelistmanager.h"
#include "ircuser.h"
#include "messagemodel.h"
#include "network.h"
#include "types.h"

ClientUserInputHandler::ClientUserInputHandler(QObject* parent)
    : BasicHandler(parent)
{
    TabCompletionSettings s;
    s.notify("CompletionSuffix", this, &ClientUserInputHandler::completionSuffixChanged);
    completionSuffixChanged(s.completionSuffix());
}

void ClientUserInputHandler::completionSuffixChanged(const QVariant& v)
{
    QString suffix = v.toString();
    QString letter = "A-Za-z";
    QString special = "\x5b-\x60\x7b-\x7d";  // NOLINT(modernize-raw-string-literal)
	_nickRx = QRegularExpression(QString("^([%1%2][%1%2\\d-]*)%3").arg(letter, special, suffix).trimmed());
}

// this would be the place for a client-side hook
void ClientUserInputHandler::handleUserInput(const BufferInfo& bufferInfo, const QString& msg)
{
    if (msg.isEmpty())
        return;

    if (!msg.startsWith('/')) {
        QRegularExpressionMatch match = _nickRx.match(msg);
        if (match.hasMatch()) {
            const Network* net = Client::network(bufferInfo.networkId());
            IrcUser* user = net ? net->ircUser(match.captured(1)) : nullptr;
            if (user)
                user->setLastSpokenTo(bufferInfo.bufferId(), QDateTime::currentDateTime().toUTC());
        }
    }

    AliasManager::CommandList clist = Client::aliasManager()->processInput(bufferInfo, msg);

    for (int i = 0; i < clist.count(); i++) {
        QString cmd = clist.at(i).second.section(' ', 0, 0).remove(0, 1).toUpper();
        QString payload = clist.at(i).second.section(' ', 1);
        handle(cmd, QGenericArgument("BufferInfo", &clist.at(i).first), QGenericArgument("QString", &payload));
    }
}

void ClientUserInputHandler::defaultHandler(const QString& cmd, const BufferInfo& bufferInfo, const QString& text)
{
    QString command = QString("/%1 %2").arg(cmd, text);
    emit sendInput(bufferInfo, command);
}

void ClientUserInputHandler::handleExec(const BufferInfo& bufferInfo, const QString& execString)
{
    auto* exec = new ExecWrapper(this);  // gets suicidal when it's done
    exec->start(bufferInfo, execString);
}

void ClientUserInputHandler::handleJoin(const BufferInfo& bufferInfo, const QString& text)
{
    auto channelName = text;
    if (channelName.isEmpty()) {
        if (bufferInfo.type() == BufferInfo::ChannelBuffer) {
            channelName = bufferInfo.bufferName();
        } else {
            Client::messageModel()->insertErrorMessage(bufferInfo, tr("/JOIN expects a channel"));
            return;
        }
    }
    switchBuffer(bufferInfo.networkId(), channelName.section(' ', 0, 0));
    // send to core
    defaultHandler("JOIN", bufferInfo, channelName);
}

void ClientUserInputHandler::handleQuery(const BufferInfo& bufferInfo, const QString& text)
{
    if (text.isEmpty()) {
        Client::messageModel()->insertErrorMessage(bufferInfo, tr("/QUERY expects at least a nick"));
        return;
    }
    switchBuffer(bufferInfo.networkId(), text.section(' ', 0, 0));
    // send to core
    defaultHandler("QUERY", bufferInfo, text);
}

void ClientUserInputHandler::handleIgnore(const BufferInfo& bufferInfo, const QString& text)
{
    if (text.isEmpty()) {
        emit Client::instance()->displayIgnoreList("");
        return;
    }
    // If rule contains no ! or @, we assume it is just a nickname, and turn it into an ignore rule for that nick
    QString rule = (text.contains('!') || text.contains('@')) ? text : text + "!*@*";

    Client::ignoreListManager()->requestAddIgnoreListItem(IgnoreListManager::IgnoreType::SenderIgnore,
                                                          rule,
                                                          false,
                                                          // Use a dynamic ignore rule, for reversibility
                                                          IgnoreListManager::StrictnessType::SoftStrictness,
                                                          // Use current network as scope
                                                          IgnoreListManager::ScopeType::NetworkScope,
                                                          Client::network(bufferInfo.networkId())->networkName(),
                                                          true);
}

void ClientUserInputHandler::handleList(const BufferInfo& bufferInfo, const QString& text)
{
    // Pass along any potential search parameters, list channels immediately
    Client::instance()->displayChannelList(bufferInfo.networkId(), text, true);
}

void ClientUserInputHandler::switchBuffer(const NetworkId& networkId, const QString& bufferName)
{
    BufferId newBufId = Client::networkModel()->bufferId(networkId, bufferName);
    if (!newBufId.isValid()) {
        Client::bufferModel()->switchToBufferAfterCreation(networkId, bufferName);
    }
    else {
        Client::bufferModel()->switchToBuffer(newBufId);
        // unhide the buffer
        ClientBufferViewManager* clientBufferViewManager = Client::bufferViewManager();
        QList<ClientBufferViewConfig*> bufferViewConfigList = clientBufferViewManager->clientBufferViewConfigs();
        foreach (ClientBufferViewConfig* bufferViewConfig, bufferViewConfigList) {
            if (bufferViewConfig->temporarilyRemovedBuffers().contains(newBufId)) {
                bufferViewConfig->requestAddBuffer(newBufId, bufferViewConfig->bufferList().length());
                // if (bufferViewConfig->sortAlphabetically()) {
                // TODO we need to trigger a sort here, but can't reach the model required
                // to get a bufferviewfilter, as the bufferviewmanager only managers configs
                // BufferViewFilter *filter = qobject_cast<BufferViewFilter *>(model());
                //}
            }
        }
    }
}
