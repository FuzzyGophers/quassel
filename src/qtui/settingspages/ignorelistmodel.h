// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

#include <memory>

#include <QAbstractItemModel>

#include "clientignorelistmanager.h"

class IgnoreListModel : public QAbstractItemModel
{
    Q_OBJECT

public:
    IgnoreListModel(QObject* parent = nullptr);

    QVariant data(const QModelIndex& index, int role) const override;
    bool setData(const QModelIndex& index, const QVariant& value, int role = Qt::EditRole) override;

    Qt::ItemFlags flags(const QModelIndex& index) const override;

    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;

    QModelIndex index(int row, int column, const QModelIndex& parent = QModelIndex()) const override;

    inline QModelIndex parent(const QModelIndex&) const override { return {}; }

    inline int rowCount(const QModelIndex& parent = QModelIndex()) const override;
    inline int columnCount(const QModelIndex& parent = QModelIndex()) const override;

    inline bool hasConfigChanged() const { return static_cast<bool>(_clonedIgnoreListManager); }
    inline bool isReady() const { return _modelReady; }

    const IgnoreListManager::IgnoreListItem& ignoreListItemAt(int row) const;
    void setIgnoreListItemAt(int row, const IgnoreListManager::IgnoreListItem& item);
    bool newIgnoreRule(const IgnoreListManager::IgnoreListItem& item);
    const QModelIndex indexOf(const QString& rule);

public slots:
    void loadDefaults();
    void removeIgnoreRule(int index);
    void revert() override;
    void commit();

signals:
    void configChanged(bool);
    void modelReady(bool);

private:
    std::unique_ptr<ClientIgnoreListManager> _clonedIgnoreListManager;
    bool _modelReady{false};

    const IgnoreListManager& ignoreListManager() const;
    IgnoreListManager& ignoreListManager();
    IgnoreListManager& cloneIgnoreListManager();

private slots:
    void clientConnected();
    void clientDisconnected();
    void initDone();
};

// Inlines
int IgnoreListModel::rowCount(const QModelIndex& parent) const
{
    Q_UNUSED(parent);
    return isReady() ? ignoreListManager().count() : 0;
}

int IgnoreListModel::columnCount(const QModelIndex& parent) const
{
    Q_UNUSED(parent);
    return isReady() ? 3 : 0;
}
