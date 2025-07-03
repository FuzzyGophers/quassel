// SPDX-FileCopyrightText: 2005-2025 Quassel Project <devel@quassel-irc.org>
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

#include <memory>

#include <QAbstractItemModel>

#include "clientaliasmanager.h"

class AliasesModel : public QAbstractItemModel
{
    Q_OBJECT

public:
    AliasesModel(QObject* parent = nullptr);

    QVariant data(const QModelIndex& index, int role) const override;
    bool setData(const QModelIndex& index, const QVariant& value, int role = Qt::EditRole) override;

    Qt::ItemFlags flags(const QModelIndex& index) const override;

    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;

    QModelIndex index(int row, int column, const QModelIndex& parent = QModelIndex()) const override;

    inline QModelIndex parent(const QModelIndex&) const override { return {}; }

    inline int rowCount(const QModelIndex& parent = QModelIndex()) const override;
    inline int columnCount(const QModelIndex& parent = QModelIndex()) const override;

    inline bool hasConfigChanged() const { return static_cast<bool>(_clonedAliasManager); }
    inline bool isReady() const { return _modelReady; }

public slots:
    void newAlias();
    void loadDefaults();
    void removeAlias(int index);
    void revert() override;
    void commit();

signals:
    void configChanged(bool);
    void modelReady(bool);

private:
    std::unique_ptr<ClientAliasManager> _clonedAliasManager;
    bool _modelReady{false};

    const AliasManager& aliasManager() const;
    AliasManager& aliasManager();
    AliasManager& cloneAliasManager();

private slots:
    void clientConnected();
    void clientDisconnected();
    void initDone();
};

// Inlines
int AliasesModel::rowCount(const QModelIndex& parent) const
{
    Q_UNUSED(parent);
    return isReady() ? aliasManager().count() : 0;
}

int AliasesModel::columnCount(const QModelIndex& parent) const
{
    Q_UNUSED(parent);
    return isReady() ? 2 : 0;
}
