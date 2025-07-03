// SPDX-FileCopyrightText: 2005-2025 Quassel Project <devel@quassel-irc.org>
// SPDX-License-Identifier: GPL-2.0-or-later

#include "titlesetter.h"

#include "abstractitemview.h"
#include "client.h"
#include "mainwin.h"

TitleSetter::TitleSetter(MainWin* parent)
    : AbstractItemView(parent)
    , _mainWin(parent)
{
}

void TitleSetter::currentChanged(const QModelIndex& current, const QModelIndex& previous)
{
    Q_UNUSED(previous);
    changeWindowTitle(current.sibling(current.row(), 0));
}

void TitleSetter::dataChanged(const QModelIndex& topLeft, const QModelIndex& bottomRight)
{
    QItemSelectionRange changedArea(topLeft, bottomRight);
    QModelIndex currentTopicIndex = selectionModel()->currentIndex().sibling(selectionModel()->currentIndex().row(), 0);
    if (changedArea.contains(currentTopicIndex))
        changeWindowTitle(currentTopicIndex);
}

void TitleSetter::changeWindowTitle(const QModelIndex& index)
{
    BufferId id = index.data(NetworkModel::BufferIdRole).value<BufferId>();
    if (!id.isValid())
        return;

    QString title;
    if (Client::networkModel()->bufferType(id) == BufferInfo::StatusBuffer)
        title = index.data().toString();
    else
        title = QString("%1 (%2)").arg(index.data().toString(), Client::networkModel()->networkName(id));
    QString newTitle = QString("%1 - %2").arg("Quassel IRC").arg(title);

    _mainWin->setWindowTitle(newTitle);
    _mainWin->setWindowIconText(newTitle);
}
