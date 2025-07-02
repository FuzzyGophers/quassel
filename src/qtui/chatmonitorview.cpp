// SPDX-License-Identifier: GPL-2.0-or-later

#include "chatmonitorview.h"

#include <QAction>
#include <QContextMenuEvent>
#include <QMenu>

#include "action.h"
#include "buffermodel.h"
#include "chatitem.h"
#include "chatlinemodel.h"
#include "chatmonitorfilter.h"
#include "chatscene.h"
#include "client.h"
#include "clientignorelistmanager.h"
#include "icon.h"
#include "messagemodel.h"
#include "networkmodel.h"
#include "qtuisettings.h"
#include "settingspagedlg.h"

#include "settingspages/chatmonitorsettingspage.h"

ChatMonitorView::ChatMonitorView(ChatMonitorFilter* filter, QWidget* parent)
    : ChatView(filter, parent)
    , _filter(filter)
{
    scene()->setSenderCutoffMode(ChatScene::CutoffLeft);
    // The normal message prefixes get replaced by the network and buffer name.  Re-add brackets for
    // all message types.
    scene()->setAlwaysBracketSender(true);
    connect(Client::instance(), &Client::coreConnectionStateChanged, this, &ChatMonitorView::coreConnectionStateChanged);
}

void ChatMonitorView::addActionsToMenu(QMenu* menu, const QPointF& pos)
{
    ChatView::addActionsToMenu(menu, pos);
    menu->addSeparator();
    auto showOwnNicksAction = new Action(tr("Show Own Messages"), menu, _filter, &ChatMonitorFilter::setShowOwnMessages);
    showOwnNicksAction->setCheckable(true);
    showOwnNicksAction->setChecked(_filter->showOwnMessages());
    menu->addAction(showOwnNicksAction);

    if (scene()->columnByScenePos(pos) == ChatLineModel::SenderColumn) {
        menu->addSeparator();

        auto showNetworkAction = new Action(tr("Show Network Name"), menu, this, &ChatMonitorView::showFieldsChanged);
        showNetworkAction->setCheckable(true);
        showNetworkAction->setChecked(_filter->showFields() & ChatMonitorFilter::NetworkField);
        showNetworkAction->setData(ChatMonitorFilter::NetworkField);
        menu->addAction(showNetworkAction);

        auto showBufferAction = new Action(tr("Show Buffer Name"), menu, this, &ChatMonitorView::showFieldsChanged);
        showBufferAction->setCheckable(true);
        showBufferAction->setChecked(_filter->showFields() & ChatMonitorFilter::BufferField);
        showBufferAction->setData(ChatMonitorFilter::BufferField);
        menu->addAction(showBufferAction);
    }

    menu->addSeparator();
    menu->addAction(new Action(icon::get("configure"), tr("Configure..."), menu, this, &ChatMonitorView::showSettingsPage));
}

void ChatMonitorView::mouseDoubleClickEvent(QMouseEvent* event)
{
    if (scene()->columnByScenePos(event->pos()) != ChatLineModel::SenderColumn) {
        ChatView::mouseDoubleClickEvent(event);
        return;
    }

    ChatItem* chatItem = scene()->chatItemAt(mapToScene(event->pos()));
    if (!chatItem) {
        event->ignore();
        return;
    }

    event->accept();
    BufferId bufferId = chatItem->data(MessageModel::BufferIdRole).value<BufferId>();
    if (!bufferId.isValid())
        return;

    Client::bufferModel()->switchToBuffer(bufferId);
}

void ChatMonitorView::showFieldsChanged(bool checked)
{
    auto* showAction = qobject_cast<QAction*>(sender());
    if (!showAction)
        return;

    if (checked)
        _filter->addShowField(showAction->data().toInt());
    else
        _filter->removeShowField(showAction->data().toInt());
}

void ChatMonitorView::showSettingsPage()
{
    SettingsPageDlg dlg(new ChatMonitorSettingsPage(), this);
    dlg.exec();
}

// connect only after client is synced to core since ChatMonitorView is created before
// the ignoreListManager
void ChatMonitorView::coreConnectionStateChanged(bool connected)
{
    if (connected)
        connect(Client::ignoreListManager(), &ClientIgnoreListManager::ignoreListChanged, _filter, &ChatMonitorFilter::invalidateFilter);
}
