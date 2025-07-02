// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

#include "uisupport-export.h"

#include <QAbstractItemDelegate>
#include <QAbstractItemModel>
#include <QItemSelection>
#include <QItemSelectionModel>
#include <QModelIndex>
#include <QPointer>
#include <QWidget>

class UISUPPORT_EXPORT AbstractItemView : public QWidget
{
    Q_OBJECT

public:
    AbstractItemView(QWidget* parent = nullptr);

    inline QAbstractItemModel* model() { return _model; }
    void setModel(QAbstractItemModel* model);

    inline QItemSelectionModel* selectionModel() const { return _selectionModel; }
    void setSelectionModel(QItemSelectionModel* selectionModel);

    inline QModelIndex currentIndex() const { return _selectionModel->currentIndex(); }

protected slots:
    virtual void closeEditor(QWidget*, QAbstractItemDelegate::EndEditHint){};
    virtual void commitData(QWidget*){};
    virtual void currentChanged(const QModelIndex&, const QModelIndex&){};
    virtual void dataChanged(const QModelIndex&, const QModelIndex&){};
    virtual void editorDestroyed(QObject*){};
    virtual void rowsAboutToBeRemoved(const QModelIndex&, int, int){};
    virtual void rowsInserted(const QModelIndex&, int, int){};
    virtual void selectionChanged(const QItemSelection&, const QItemSelection&){};

protected:
    QPointer<QAbstractItemModel> _model;
    QPointer<QItemSelectionModel> _selectionModel;
};
