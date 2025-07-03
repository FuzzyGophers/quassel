// SPDX-FileCopyrightText: 2005-2025 Quassel Project <devel@quassel-irc.org>
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

#include "client-export.h"

#include <QItemSelectionModel>
#include <QObject>

class QAbstractItemModel;

class CLIENT_EXPORT SelectionModelSynchronizer : public QObject
{
    Q_OBJECT

public:
    SelectionModelSynchronizer(QAbstractItemModel* parent = nullptr);

    void synchronizeSelectionModel(QItemSelectionModel* selectionModel);
    void removeSelectionModel(QItemSelectionModel* selectionModel);

    inline QAbstractItemModel* model() { return _model; }
    inline QItemSelectionModel* selectionModel() const { return const_cast<QItemSelectionModel*>(&_selectionModel); }
    inline QModelIndex currentIndex() const { return _selectionModel.currentIndex(); }
    inline QItemSelection currentSelection() const { return _selectionModel.selection(); }

private slots:
    void syncedCurrentChanged(const QModelIndex& current, const QModelIndex& previous);
    void syncedSelectionChanged(const QItemSelection& selected, const QItemSelection& previous);

    void setCurrentIndex(const QModelIndex& index);
    void setCurrentSelection(const QItemSelection& selection);

    void currentChanged(const QModelIndex& current, const QModelIndex& previous);
    void selectionChanged(const QItemSelection& selected, const QItemSelection& deselected);

    void selectionModelDestroyed(QObject* object);

private:
    QAbstractItemModel* _model;
    QItemSelectionModel _selectionModel;
    bool _changeCurrentEnabled{true};
    bool _changeSelectionEnabled{true};

    bool checkBaseModel(QItemSelectionModel* model);
    QModelIndex mapFromSource(const QModelIndex& sourceIndex, const QItemSelectionModel* selectionModel);
    QItemSelection mapSelectionFromSource(const QItemSelection& sourceSelection, const QItemSelectionModel* selectionModel);
    QModelIndex mapToSource(const QModelIndex& index, QItemSelectionModel* selectionModel);
    QItemSelection mapSelectionToSource(const QItemSelection& selection, QItemSelectionModel* selectionModel);

    QSet<QItemSelectionModel*> _selectionModels;
};
