// SPDX-FileCopyrightText: 2005-2025 Quassel Project <devel@quassel-irc.org>
// SPDX-License-Identifier: GPL-2.0-or-later

#include "nickview.h"

#include <QApplication>
#include <QDebug>
#include <QHeaderView>
#include <QMenu>
#include <QScrollBar>

#include "buffermodel.h"
#include "client.h"
#include "contextmenuactionprovider.h"
#include "graphicalui.h"
#include "networkmodel.h"
#include "nickview.h"
#include "nickviewfilter.h"
#include "types.h"

NickView::NickView(QWidget* parent)
    : TreeViewTouch(parent)
{
    setIndentation(10);
    header()->hide();
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setSortingEnabled(true);
    sortByColumn(0, Qt::AscendingOrder);

    setContextMenuPolicy(Qt::CustomContextMenu);
    setSelectionMode(QAbstractItemView::ExtendedSelection);

    setAnimated(true);

    connect(this, &QWidget::customContextMenuRequested, this, &NickView::showContextMenu);

#if defined Q_OS_MACOS || defined Q_OS_WIN
    // afaik this is better on Mac and Windows
    connect(this, &QAbstractItemView::activated, this, &NickView::startQuery);
#else
    connect(this, &QAbstractItemView::doubleClicked, this, &NickView::startQuery);
#endif
}

void NickView::init()
{
    if (!model())
        return;

    for (int i = 1; i < model()->columnCount(); i++)
        setColumnHidden(i, true);

    connect(selectionModel(), &QItemSelectionModel::currentChanged, this, &NickView::selectionUpdated);
    connect(selectionModel(), &QItemSelectionModel::selectionChanged, this, &NickView::selectionUpdated);
}

void NickView::setModel(QAbstractItemModel* model_)
{
    if (model())
        disconnect(model(), nullptr, this, nullptr);

    TreeViewTouch::setModel(model_);
    init();
}

void NickView::rowsInserted(const QModelIndex& parent, int start, int end)
{
    TreeViewTouch::rowsInserted(parent, start, end);
    if (model()->data(parent, NetworkModel::ItemTypeRole) == NetworkModel::UserCategoryItemType && !isExpanded(parent)) {
        unanimatedExpandAll();
    }
}

void NickView::setRootIndex(const QModelIndex& index)
{
    QAbstractItemView::setRootIndex(index);
    if (index.isValid())
        unanimatedExpandAll();
}

QModelIndexList NickView::selectedIndexes() const
{
    QModelIndexList indexList = TreeViewTouch::selectedIndexes();

    // make sure the item we clicked on is first
    if (indexList.contains(currentIndex())) {
        indexList.removeAll(currentIndex());
        indexList.prepend(currentIndex());
    }

    return indexList;
}

void NickView::unanimatedExpandAll()
{
    // since of Qt Version 4.8.0 the default expandAll will not properly work if
    // animations are enabled. Therefore we perform an unanimated expand when a
    // model is set or a toplevel node is inserted.
    bool wasAnimated = isAnimated();
    setAnimated(false);
    expandAll();
    setAnimated(wasAnimated);
}

void NickView::showContextMenu(const QPoint& pos)
{
    Q_UNUSED(pos);

    QMenu contextMenu(this);
    GraphicalUi::contextMenuActionProvider()->addActions(&contextMenu, selectedIndexes());
    contextMenu.exec(QCursor::pos());
}

void NickView::startQuery(const QModelIndex& index)
{
    if (index.data(NetworkModel::ItemTypeRole) != NetworkModel::IrcUserItemType)
        return;

    auto* ircUser = qobject_cast<IrcUser*>(index.data(NetworkModel::IrcUserRole).value<QObject*>());
    NetworkId networkId = index.data(NetworkModel::NetworkIdRole).value<NetworkId>();
    if (!ircUser || !networkId.isValid())
        return;

    Client::bufferModel()->switchToOrStartQuery(networkId, ircUser->nick());
}
