// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

#include "uisupport-export.h"

#include <QTreeView>

#include "bufferinfo.h"
#include "treeviewtouch.h"

class UISUPPORT_EXPORT NickView : public TreeViewTouch
{
    Q_OBJECT

public:
    NickView(QWidget* parent = nullptr);

protected:
    void rowsInserted(const QModelIndex& parent, int start, int end) override;

    //! This reimplementation ensures that the current index is first in list
    QModelIndexList selectedIndexes() const override;

    void unanimatedExpandAll();

public slots:
    void setModel(QAbstractItemModel* model) override;
    void setRootIndex(const QModelIndex& index) override;
    void init();
    void showContextMenu(const QPoint& pos);
    void startQuery(const QModelIndex& modelIndex);

signals:
    void selectionUpdated();

private:
    friend class NickListWidget;  // needs selectedIndexes()
};
