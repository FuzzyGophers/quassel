// SPDX-FileCopyrightText: 2005-2025 Quassel Project <devel@quassel-irc.org>
// SPDX-License-Identifier: GPL-2.0-or-later

#include "tabcompleter.h"

#include <QRegularExpression>
#include <QRegularExpressionMatch>

#include "action.h"
#include "actioncollection.h"
#include "buffermodel.h"
#include "client.h"
#include "graphicalui.h"
#include "ircchannel.h"
#include "ircuser.h"
#include "multilineedit.h"
#include "network.h"
#include "networkmodel.h"
#include "uisettings.h"

const Network* TabCompleter::_currentNetwork;
BufferId TabCompleter::_currentBufferId;
QString TabCompleter::_currentBufferName;
TabCompleter::Type TabCompleter::_completionType;

TabCompleter::TabCompleter(MultiLineEdit* _lineEdit)
    : QObject(_lineEdit)
    , _lineEdit(_lineEdit)
    , _enabled(false)
    , _nickSuffix(": ")
{
    // This Action just serves as a container for the custom shortcut and isn't actually handled;
    // apparently, using tab as an Action shortcut in an input widget is unreliable on some platforms (e.g. OS/2)
    _lineEdit->installEventFilter(this);
    ActionCollection* coll = GraphicalUi::actionCollection("General");
    QAction* a = coll->addAction("TabCompletionKey",
                                 new Action(tr("Tab completion"), coll, this, &TabCompleter::onTabCompletionKey, QKeySequence(Qt::Key_Tab)));
    a->setEnabled(false);  // avoid catching the shortcut
}

void TabCompleter::onTabCompletionKey()
{
    // do nothing; we use the event filter instead
}

void TabCompleter::buildCompletionList()
{
    // ensure a safe state in case we return early.
    _completionMap.clear();
    _nextCompletion = _completionMap.begin();

    // this is the first time tab is pressed -> build up the completion list and it's iterator
    QModelIndex currentIndex = Client::bufferModel()->currentIndex();
    _currentBufferId = currentIndex.data(NetworkModel::BufferIdRole).value<BufferId>();
    if (!_currentBufferId.isValid())
        return;

    NetworkId networkId = currentIndex.data(NetworkModel::NetworkIdRole).value<NetworkId>();
    _currentBufferName = currentIndex.sibling(currentIndex.row(), 0).data().toString();

    _currentNetwork = Client::network(networkId);
    if (!_currentNetwork)
        return;

    QString tabAbbrev = _lineEdit->text().left(_lineEdit->cursorPosition()).section(QRegularExpression(R"([^#\w\d-_\[\]{}|`^.\\])"), -1, -1);
    QRegularExpression regex(QString(R"(^[-_\[\]{}|`^.\\]*)").append(QRegularExpression::escape(tabAbbrev)),
                             QRegularExpression::CaseInsensitiveOption);

    // channel completion - add all channels of the current network to the map
    if (tabAbbrev.startsWith('#')) {
        _completionType = ChannelTab;
        for (IrcChannel* ircChannel : _currentNetwork->ircChannels()) {
            if (regex.match(ircChannel->name()).hasMatch())
                _completionMap[ircChannel->name()] = ircChannel->name();
        }
    }
    else {
        // user completion
        _completionType = UserTab;
        switch (static_cast<BufferInfo::Type>(currentIndex.data(NetworkModel::BufferTypeRole).toInt())) {
        case BufferInfo::ChannelBuffer: {  // scope is needed for local var declaration
            IrcChannel* channel = _currentNetwork->ircChannel(_currentBufferName);
            if (!channel)
                return;
            for (IrcUser* ircUser : channel->ircUsers()) {
                if (regex.match(ircUser->nick()).hasMatch())
                    _completionMap[ircUser->nick().toLower()] = ircUser->nick();
            }
        } break;
        case BufferInfo::QueryBuffer:
            if (regex.match(_currentBufferName).hasMatch())
                _completionMap[_currentBufferName.toLower()] = _currentBufferName;
            // fallthrough
        case BufferInfo::StatusBuffer:
            if (!_currentNetwork->myNick().isEmpty() && regex.match(_currentNetwork->myNick()).hasMatch())
                _completionMap[_currentNetwork->myNick().toLower()] = _currentNetwork->myNick();
            break;
        default:
            return;
        }
    }

    _nextCompletion = _completionMap.begin();
    _lastCompletionLength = tabAbbrev.length();
}

void TabCompleter::complete()
{
    TabCompletionSettings s;
    _nickSuffix = s.completionSuffix();

    if (!_enabled) {
        buildCompletionList();
        _enabled = true;
    }

    if (_nextCompletion != _completionMap.end()) {
        // clear previous completion
        for (int i = 0; i < _lastCompletionLength; i++) {
            _lineEdit->backspace();
        }

        // insert completion
        _lineEdit->insert(*_nextCompletion);

        // remember charcount to delete next time and advance to next completion
        _lastCompletionLength = _nextCompletion->length();
        _nextCompletion++;

        // we're completing the first word of the line
        if (_completionType == UserTab && _lineEdit->cursorPosition() == _lastCompletionLength) {
            _lineEdit->insert(_nickSuffix);
            _lastCompletionLength += _nickSuffix.length();
        }
        else if (s.addSpaceMidSentence()) {
            _lineEdit->addCompletionSpace();
            _lastCompletionLength++;
        }

        // we're at the end of the list -> start over again
    }
    else {
        if (!_completionMap.isEmpty()) {
            _nextCompletion = _completionMap.begin();
            complete();
        }
    }
}

void TabCompleter::reset()
{
    _enabled = false;
}

bool TabCompleter::eventFilter(QObject* obj, QEvent* event)
{
    if (obj != _lineEdit || event->type() != QEvent::KeyPress)
        return QObject::eventFilter(obj, event);

    auto* keyEvent = static_cast<QKeyEvent*>(event);

    QAction* tabCompletionAction = GraphicalUi::actionCollection("General")->action("TabCompletionKey");
    if (keyEvent->keyCombination() == tabCompletionAction->shortcut()[0])
        complete();
    else
        reset();

    return false;
}

// this determines the sort order
bool TabCompleter::CompletionKey::operator<(const CompletionKey& other) const
{
    switch (_completionType) {
    case UserTab: {
        IrcUser* thisUser = _currentNetwork->ircUser(this->contents);
        if (thisUser && _currentNetwork->isMe(thisUser))
            return false;

        IrcUser* thatUser = _currentNetwork->ircUser(other.contents);
        if (thatUser && _currentNetwork->isMe(thatUser))
            return true;

        if (!thisUser || !thatUser)
            return QString::localeAwareCompare(this->contents, other.contents) < 0;

        QDateTime thisSpokenTo = thisUser->lastSpokenTo(_currentBufferId);
        QDateTime thatSpokenTo = thatUser->lastSpokenTo(_currentBufferId);

        if (thisSpokenTo.isValid() || thatSpokenTo.isValid())
            return thisSpokenTo > thatSpokenTo;

        QDateTime thisTime = thisUser->lastChannelActivity(_currentBufferId);
        QDateTime thatTime = thatUser->lastChannelActivity(_currentBufferId);

        if (thisTime.isValid() || thatTime.isValid())
            return thisTime > thatTime;
    } break;
    case ChannelTab:
        if (QString::compare(_currentBufferName, this->contents, Qt::CaseInsensitive) == 0)
            return true;

        if (QString::compare(_currentBufferName, other.contents, Qt::CaseInsensitive) == 0)
            return false;
        break;
    default:
        break;
    }

    return QString::localeAwareCompare(this->contents, other.contents) < 0;
}
