// SPDX-FileCopyrightText: 2005-2025 Quassel Project <devel@quassel-irc.org>
// SPDX-License-Identifier: GPL-2.0-or-later

#include "selectionmodelsynchronizer.h"

#include <QAbstractItemModel>
#include <QAbstractProxyModel>
#include <QDebug>

SelectionModelSynchronizer::SelectionModelSynchronizer(QAbstractItemModel* parent)
    : QObject(parent)
    , _model(parent)
    , _selectionModel(parent)
{
    connect(&_selectionModel, &QItemSelectionModel::currentChanged, this, &SelectionModelSynchronizer::currentChanged);
    connect(&_selectionModel, &QItemSelectionModel::selectionChanged, this, &SelectionModelSynchronizer::selectionChanged);
}

bool SelectionModelSynchronizer::checkBaseModel(QItemSelectionModel* selectionModel)
{
    if (!selectionModel)
        return false;

    const QAbstractItemModel* baseModel = selectionModel->model();
    const QAbstractProxyModel* proxyModel = nullptr;
    while ((proxyModel = qobject_cast<const QAbstractProxyModel*>(baseModel)) != nullptr) {
        baseModel = proxyModel->sourceModel();
        if (baseModel == model())
            break;
    }
    return baseModel == model();
}

void SelectionModelSynchronizer::synchronizeSelectionModel(QItemSelectionModel* selectionModel)
{
    if (!checkBaseModel(selectionModel)) {
        qWarning() << "cannot Synchronize SelectionModel" << selectionModel << "which has a different baseModel()";
        return;
    }

    if (_selectionModels.contains(selectionModel)) {
        selectionModel->setCurrentIndex(mapFromSource(currentIndex(), selectionModel), QItemSelectionModel::Current);
        selectionModel->select(mapSelectionFromSource(currentSelection(), selectionModel), QItemSelectionModel::ClearAndSelect);
        return;
    }

    connect(selectionModel, &QItemSelectionModel::currentChanged, this, &SelectionModelSynchronizer::syncedCurrentChanged);
    connect(selectionModel, &QItemSelectionModel::selectionChanged, this, &SelectionModelSynchronizer::syncedSelectionChanged);

    connect(selectionModel, &QObject::destroyed, this, &SelectionModelSynchronizer::selectionModelDestroyed);

    _selectionModels << selectionModel;
}

void SelectionModelSynchronizer::removeSelectionModel(QItemSelectionModel* model)
{
    disconnect(model, nullptr, this, nullptr);
    disconnect(this, nullptr, model, nullptr);
    selectionModelDestroyed(model);
}

void SelectionModelSynchronizer::selectionModelDestroyed(QObject* object)
{
    auto* model = static_cast<QItemSelectionModel*>(object);
    QSet<QItemSelectionModel*>::iterator iter = _selectionModels.begin();
    while (iter != _selectionModels.end()) {
        if (*iter == model) {
            iter = _selectionModels.erase(iter);
        }
        else {
            ++iter;
        }
    }
}

void SelectionModelSynchronizer::syncedCurrentChanged(const QModelIndex& current, const QModelIndex& previous)
{
    Q_UNUSED(previous);

    if (!_changeCurrentEnabled)
        return;

    auto* selectionModel = qobject_cast<QItemSelectionModel*>(sender());
    Q_ASSERT(selectionModel);
    QModelIndex newSourceCurrent = mapToSource(current, selectionModel);
    if (newSourceCurrent.isValid() && newSourceCurrent != currentIndex())
        setCurrentIndex(newSourceCurrent);
}

void SelectionModelSynchronizer::syncedSelectionChanged(const QItemSelection& selected, const QItemSelection& deselected)
{
    Q_UNUSED(selected);
    Q_UNUSED(deselected);

    if (!_changeSelectionEnabled)
        return;

    auto* selectionModel = qobject_cast<QItemSelectionModel*>(sender());
    Q_ASSERT(selectionModel);

    QItemSelection mappedSelection = selectionModel->selection();
    QItemSelection currentSelectionMapped = mapSelectionFromSource(currentSelection(), selectionModel);

    QItemSelection checkSelection = currentSelectionMapped;
    checkSelection.merge(mappedSelection, QItemSelectionModel::Deselect);
    if (checkSelection.isEmpty()) {
        // that means the new selection contains the current selection (currentSel - newSel = {})
        checkSelection = mappedSelection;
        checkSelection.merge(currentSelectionMapped, QItemSelectionModel::Deselect);
        if (checkSelection.isEmpty()) {
            // that means the current selection contains the new selection (newSel - currentSel = {})
            // -> currentSel == newSel
            return;
        }
    }
    setCurrentSelection(mapSelectionToSource(mappedSelection, selectionModel));
}

QModelIndex SelectionModelSynchronizer::mapFromSource(const QModelIndex& sourceIndex, const QItemSelectionModel* selectionModel)
{
    Q_ASSERT(selectionModel);

    QModelIndex mappedIndex = sourceIndex;

    // make a list of all involved proxies, wie have to traverse backwards
    QList<const QAbstractProxyModel*> proxyModels;
    const QAbstractItemModel* baseModel = selectionModel->model();
    const QAbstractProxyModel* proxyModel = nullptr;
    while ((proxyModel = qobject_cast<const QAbstractProxyModel*>(baseModel)) != nullptr) {
        if (baseModel == model())
            break;
        proxyModels << proxyModel;
        baseModel = proxyModel->sourceModel();
    }

    // now traverse it;
    for (int i = proxyModels.count() - 1; i >= 0; i--) {
        mappedIndex = proxyModels[i]->mapFromSource(mappedIndex);
    }

    return mappedIndex;
}

QItemSelection SelectionModelSynchronizer::mapSelectionFromSource(const QItemSelection& sourceSelection,
                                                                  const QItemSelectionModel* selectionModel)
{
    Q_ASSERT(selectionModel);

    QItemSelection mappedSelection = sourceSelection;

    // make a list of all involved proxies, wie have to traverse backwards
    QList<const QAbstractProxyModel*> proxyModels;
    const QAbstractItemModel* baseModel = selectionModel->model();
    const QAbstractProxyModel* proxyModel = nullptr;
    while ((proxyModel = qobject_cast<const QAbstractProxyModel*>(baseModel)) != nullptr) {
        if (baseModel == model())
            break;
        proxyModels << proxyModel;
        baseModel = proxyModel->sourceModel();
    }

    // now traverse it;
    for (int i = proxyModels.count() - 1; i >= 0; i--) {
        mappedSelection = proxyModels[i]->mapSelectionFromSource(mappedSelection);
    }
    return mappedSelection;
}

QModelIndex SelectionModelSynchronizer::mapToSource(const QModelIndex& index, QItemSelectionModel* selectionModel)
{
    Q_ASSERT(selectionModel);

    QModelIndex sourceIndex = index;
    const QAbstractItemModel* baseModel = selectionModel->model();
    const QAbstractProxyModel* proxyModel = nullptr;
    while ((proxyModel = qobject_cast<const QAbstractProxyModel*>(baseModel)) != nullptr) {
        sourceIndex = proxyModel->mapToSource(sourceIndex);
        baseModel = proxyModel->sourceModel();
        if (baseModel == model())
            break;
    }
    return sourceIndex;
}

QItemSelection SelectionModelSynchronizer::mapSelectionToSource(const QItemSelection& selection, QItemSelectionModel* selectionModel)
{
    Q_ASSERT(selectionModel);

    QItemSelection sourceSelection = selection;
    const QAbstractItemModel* baseModel = selectionModel->model();
    const QAbstractProxyModel* proxyModel = nullptr;
    while ((proxyModel = qobject_cast<const QAbstractProxyModel*>(baseModel)) != nullptr) {
        sourceSelection = proxyModel->mapSelectionToSource(sourceSelection);
        baseModel = proxyModel->sourceModel();
        if (baseModel == model())
            break;
    }
    return sourceSelection;
}

void SelectionModelSynchronizer::setCurrentIndex(const QModelIndex& index)
{
    _selectionModel.setCurrentIndex(index, QItemSelectionModel::Current);
}

void SelectionModelSynchronizer::setCurrentSelection(const QItemSelection& selection)
{
    _selectionModel.select(selection, QItemSelectionModel::ClearAndSelect);
}

void SelectionModelSynchronizer::currentChanged(const QModelIndex& current, const QModelIndex& previous)
{
    Q_UNUSED(previous);

    _changeCurrentEnabled = false;
    QSet<QItemSelectionModel*>::iterator iter = _selectionModels.begin();
    while (iter != _selectionModels.end()) {
        (*iter)->setCurrentIndex(mapFromSource(current, (*iter)), QItemSelectionModel::Current);
        ++iter;
    }
    _changeCurrentEnabled = true;

    // Trigger a dataChanged() signal from the base model to update all proxy models (e.g. filters).
    // Since signals are protected, we have to use invokeMethod for faking signal emission.
    if (previous.isValid()) {
        QMetaObject::invokeMethod(model(), "dataChanged", Qt::DirectConnection, Q_ARG(QModelIndex, previous), Q_ARG(QModelIndex, previous));
    }
}

void SelectionModelSynchronizer::selectionChanged(const QItemSelection& selected, const QItemSelection& deselected)
{
    Q_UNUSED(selected);
    Q_UNUSED(deselected);

    _changeSelectionEnabled = false;
    QSet<QItemSelectionModel*>::iterator iter = _selectionModels.begin();
    while (iter != _selectionModels.end()) {
        (*iter)->select(mapSelectionFromSource(currentSelection(), (*iter)), QItemSelectionModel::ClearAndSelect);
        ++iter;
    }
    _changeSelectionEnabled = true;
}
