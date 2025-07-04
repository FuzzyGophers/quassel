// SPDX-FileCopyrightText: 2005-2025 Quassel Project <devel@quassel-irc.org>
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

#include "client-export.h"

#include <QCoreApplication>
#include <QDebug>
#include <QNetworkProxy>
#include <QUuid>
#include <QVariantMap>

#include "types.h"

class CLIENT_EXPORT CoreAccount
{
    Q_DECLARE_TR_FUNCTIONS(CoreAccount)

public:
    CoreAccount(AccountId accountId = 0);
    virtual ~CoreAccount() = default;

    inline bool isValid() const { return accountId().isValid(); }
    inline AccountId accountId() const { return _accountId; }
    inline QString accountName() const { return isInternal() ? tr("Internal Core") : _accountName; }
    inline QUuid uuid() const { return _uuid; }
    inline bool isInternal() const { return _internal; }

    inline QString user() const { return _user; }
    inline bool storePassword() const { return _storePassword; }
    inline QString hostName() const { return _hostName; }
    inline uint port() const { return _port; }

    inline QNetworkProxy::ProxyType proxyType() const { return _proxyType; }
    inline QString proxyUser() const { return _proxyUser; }
    inline QString proxyHostName() const { return _proxyHostName; }
    inline uint proxyPort() const { return _proxyPort; }

    void setAccountId(AccountId id);
    void setAccountName(const QString& accountName);
    void setUuid(const QUuid& uuid);
    void setInternal(bool);

    void setUser(const QString& user);
    void setStorePassword(bool);
    void setHostName(const QString& hostname);
    void setPort(uint port);

    void setProxyType(QNetworkProxy::ProxyType);
    void setProxyUser(const QString&);
    void setProxyHostName(const QString&);
    void setProxyPort(uint);

    /* These might be overridden for KWallet/QtKeychain support */
    virtual inline QString password() const { return _password; }
    virtual void setPassword(const QString& password);
    virtual inline QString proxyPassword() const { return _proxyPassword; }
    virtual void setProxyPassword(const QString&);

    virtual QVariantMap toVariantMap(bool forcePassword = false) const;
    virtual void fromVariantMap(const QVariantMap&);

    bool operator==(const CoreAccount& other) const;
    bool operator!=(const CoreAccount& other) const;

private:
    AccountId _accountId;
    QString _accountName;
    QUuid _uuid;
    bool _internal;
    QString _user, _password, _hostName;
    uint _port;
    bool _storePassword{};
    QNetworkProxy::ProxyType _proxyType;
    QString _proxyUser, _proxyPassword, _proxyHostName;
    uint _proxyPort;
};

QDebug operator<<(QDebug dbg, const CoreAccount& msg);
