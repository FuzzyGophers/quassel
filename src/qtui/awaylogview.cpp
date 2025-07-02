// SPDX-License-Identifier: GPL-2.0-or-later

#include "awaylogview.h"

#include <QAction>
#include <QMenu>

#include "action.h"
#include "awaylogfilter.h"
#include "chatlinemodel.h"
#include "chatscene.h"

AwayLogView::AwayLogView(AwayLogFilter* filter, QWidget* parent)
    : ChatMonitorView(filter, parent)
{
    setWindowTitle(tr("Away Log"));
}

void AwayLogView::addActionsToMenu(QMenu* menu, const QPointF& pos)
{
    ChatView::addActionsToMenu(menu, pos);
    if (!menu->isEmpty())
        menu->addSeparator();

    if (scene()->columnByScenePos(pos) == ChatLineModel::SenderColumn) {
        menu->addSeparator();

        auto* showNetworkAction = new Action(tr("Show Network Name"), menu, this, &AwayLogView::showFieldsChanged);
        showNetworkAction->setCheckable(true);
        showNetworkAction->setChecked(filter()->showFields() & ChatMonitorFilter::NetworkField);
        showNetworkAction->setData(ChatMonitorFilter::NetworkField);
        menu->addAction(showNetworkAction);

        auto* showBufferAction = new Action(tr("Show Buffer Name"), menu, this, &AwayLogView::showFieldsChanged);
        showBufferAction->setCheckable(true);
        showBufferAction->setChecked(filter()->showFields() & ChatMonitorFilter::BufferField);
        showBufferAction->setData(ChatMonitorFilter::BufferField);
        menu->addAction(showBufferAction);
    }
}
