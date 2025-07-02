// SPDX-License-Identifier: GPL-2.0-or-later

#include "resourcetreedlg.h"

#include <QDir>
#include <QList>

#include "treemodel.h"

namespace {

void addEntries(const QString& dir, AbstractTreeItem* parentItem)
{
    auto entries = QDir{dir}.entryInfoList(QDir::AllEntries | QDir::NoDotAndDotDot, QDir::Name | QDir::DirsFirst);
    QList<AbstractTreeItem*> itemList;
    for (auto&& entry : entries) {
        auto item = new SimpleTreeItem({entry.fileName(), entry.size()}, parentItem);
        itemList << item;
        if (entry.isDir()) {
            addEntries(entry.absoluteFilePath(), item);
        }
    }
    parentItem->newChilds(itemList);
}

}  // namespace

ResourceTreeDlg::ResourceTreeDlg(QWidget* parent)
    : QDialog(parent)
{
    ui.setupUi(this);
    setAttribute(Qt::WA_DeleteOnClose, true);

    // We can't use QFileSystemModel, because it doesn't support the virtual resource file system :(
    auto model = new TreeModel({tr("File"), tr("Size")}, this);
    addEntries(":/", model->root());
    ui.treeView->setModel(model);
    ui.treeView->resizeColumnToContents(0);
}
