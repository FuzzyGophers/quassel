// SPDX-FileCopyrightText: 2005-2025 Quassel Project <devel@quassel-irc.org>
// SPDX-License-Identifier: GPL-2.0-or-later

#include "coreignorelistmanager.h"

#include "core.h"
#include "coresession.h"

CoreIgnoreListManager::CoreIgnoreListManager(CoreSession* parent)
    : IgnoreListManager(parent)
{
    auto* session = qobject_cast<CoreSession*>(parent);
    if (!session) {
        qWarning() << "CoreIgnoreListManager: unable to load IgnoreList. Parent is not a Coresession!";
        // loadDefaults();
        return;
    }

    initSetIgnoreList(Core::getUserSetting(session->user(), "IgnoreList").toMap());

    // we store our settings whenever they change
    connect(this, &SyncableObject::updatedRemotely, this, &CoreIgnoreListManager::save);

    // if(isEmpty())
    // loadDefaults();
}

IgnoreListManager::StrictnessType CoreIgnoreListManager::match(const RawMessage& rawMsg, const QString& networkName)
{
    // StrictnessType _match(const QString &msgContents, const QString &msgSender, Message::Type msgType, const QString &network, const QString &bufferName);
    return _match(rawMsg.text, rawMsg.sender, rawMsg.type, networkName, rawMsg.target);
}

void CoreIgnoreListManager::save() const
{
    auto* session = qobject_cast<CoreSession*>(parent());
    if (!session) {
        qWarning() << "CoreIgnoreListManager: unable to save IgnoreList. Parent is not a Coresession!";
        return;
    }

    Core::setUserSetting(session->user(), "IgnoreList", initIgnoreList());
}

// void CoreIgnoreListManager::loadDefaults() {
//  foreach(IgnoreListItem item, IgnoreListManager::defaults()) {
//    addIgnoreListItem(item.contents(), item.isRegEx(), item.strictness(), item.scope(),
//                      item.scopeRule());
//  }
//}
