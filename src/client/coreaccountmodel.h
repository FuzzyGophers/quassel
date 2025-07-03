// SPDX-FileCopyrightText: 2005-2025 Quassel Project <devel@quassel-irc.org>
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

#include "client-export.h"

#include <QAbstractListModel>
#include <QUuid>

#include "coreaccount.h"

class CLIENT_EXPORT CoreAccountModel : public QAbstractListModel
{
    Q_OBJECT

public:
    enum
    {
        AccountIdRole = Qt::UserRole,
        UuidRole
    };

    CoreAccountModel(QObject* parent = nullptr);
    CoreAccountModel(const CoreAccountModel* other, QObject* parent = nullptr);

    inline int rowCount(const QModelIndex& parent = QModelIndex()) const override;
    QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const override;

    CoreAccount account(const QModelIndex&) const;
    CoreAccount account(AccountId) const;
    QList<CoreAccount> accounts() const;
    QList<AccountId> accountIds() const;
    QModelIndex accountIndex(AccountId id) const;

    inline AccountId internalAccount() const;

    AccountId createOrUpdateAccount(const CoreAccount& newAccountData);
    CoreAccount takeAccount(AccountId);
    void removeAccount(AccountId);

    void update(const CoreAccountModel* other);

    bool operator==(const CoreAccountModel& other) const;
    bool operator!=(const CoreAccountModel& other) const;

public slots:
    void save();
    void load();
    void clear();

protected:
    void insertAccount(const CoreAccount&);
    int findAccountIdx(AccountId) const;

private:
    int listIndex(AccountId);

    QList<CoreAccount> _accounts;
    QSet<AccountId> _removedAccounts;
    AccountId _internalAccount;
};

// Inlines
int CoreAccountModel::rowCount(const QModelIndex&) const
{
    return _accounts.count();
}

AccountId CoreAccountModel::internalAccount() const
{
    return _internalAccount;
}
