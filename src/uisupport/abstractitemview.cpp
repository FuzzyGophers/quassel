// SPDX-FileCopyrightText: 2005-2025 Quassel Project <devel@quassel-irc.org>
// SPDX-License-Identifier: GPL-2.0-or-later

#include "abstractitemview.h"

AbstractItemView::AbstractItemView(QWidget* parent)
    : QWidget(parent)
    , _model(nullptr)
    , _selectionModel(nullptr)
{
}

void AbstractItemView::setModel(QAbstractItemModel* model)
{
    if (_model) {
        disconnect(_model, nullptr, this, nullptr);
    }
    _model = model;
    connect(model, &QAbstractItemModel::dataChanged, this, &AbstractItemView::dataChanged);
    connect(model, &QAbstractItemModel::rowsAboutToBeRemoved, this, &AbstractItemView::rowsAboutToBeRemoved);
    connect(model, &QAbstractItemModel::rowsInserted, this, &AbstractItemView::rowsInserted);
}

void AbstractItemView::setSelectionModel(QItemSelectionModel* selectionModel)
{
    if (_selectionModel) {
        disconnect(_selectionModel, nullptr, this, nullptr);
    }
    _selectionModel = selectionModel;
    connect(selectionModel, &QItemSelectionModel::currentChanged, this, &AbstractItemView::currentChanged);
    connect(selectionModel, &QItemSelectionModel::selectionChanged, this, &AbstractItemView::selectionChanged);
}
