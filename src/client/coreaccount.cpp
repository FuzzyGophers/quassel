// SPDX-FileCopyrightText: 2005-2025 Quassel Project <devel@quassel-irc.org>
// SPDX-License-Identifier: GPL-2.0-or-later

#include "coreaccount.h"

CoreAccount::CoreAccount(AccountId accountId)
{
    _accountId = accountId;
    _internal = false;
    _port = 4242;
    _storePassword = false;
    _proxyType = QNetworkProxy::DefaultProxy;
    _proxyPort = 8080;
}

void CoreAccount::setAccountId(AccountId id)
{
    _accountId = id;
}

void CoreAccount::setAccountName(const QString& name)
{
    _accountName = name;
}

void CoreAccount::setUuid(const QUuid& uuid)
{
    _uuid = uuid;
}

void CoreAccount::setInternal(bool internal)
{
    _internal = internal;
}

void CoreAccount::setUser(const QString& user)
{
    _user = user;
}

void CoreAccount::setPassword(const QString& password)
{
    _password = password;
}

void CoreAccount::setStorePassword(bool store)
{
    _storePassword = store;
}

void CoreAccount::setHostName(const QString& hostname)
{
    _hostName = hostname;
}

void CoreAccount::setPort(uint port)
{
    _port = port;
}

void CoreAccount::setProxyType(QNetworkProxy::ProxyType type)
{
    _proxyType = type;
}

void CoreAccount::setProxyUser(const QString& proxyUser)
{
    _proxyUser = proxyUser;
}

void CoreAccount::setProxyPassword(const QString& proxyPassword)
{
    _proxyPassword = proxyPassword;
}

void CoreAccount::setProxyHostName(const QString& proxyHostName)
{
    _proxyHostName = proxyHostName;
}

void CoreAccount::setProxyPort(uint proxyPort)
{
    _proxyPort = proxyPort;
}

QVariantMap CoreAccount::toVariantMap(bool forcePassword) const
{
    QVariantMap v;
    v["AccountId"] = accountId().toInt();  // can't use AccountId because then comparison fails
    v["AccountName"] = accountName();
    v["Uuid"] = uuid().toString();
    v["Internal"] = isInternal();
    v["User"] = user();
    if (_storePassword || forcePassword)
        v["Password"] = password();
    else
        v["Password"] = QString();
    v["StorePassword"] = storePassword();
    v["HostName"] = hostName();
    v["Port"] = port();
    v["ProxyType"] = proxyType();
    v["ProxyUser"] = proxyUser();
    v["ProxyPassword"] = proxyPassword();
    v["ProxyHostName"] = proxyHostName();
    v["ProxyPort"] = proxyPort();
    return v;
}

void CoreAccount::fromVariantMap(const QVariantMap& v)
{
    setAccountId((AccountId)v.value("AccountId").toInt());
    setAccountName(v.value("AccountName").toString());
    setUuid(QUuid(v.value("Uuid").toString()));
    setInternal(v.value("Internal").toBool());
    setUser(v.value("User").toString());
    setPassword(v.value("Password").toString());
    setStorePassword(v.value("StorePassword").toBool());
    setHostName(v.value("HostName").toString());
    setPort(v.value("Port").toUInt());
    setProxyType((QNetworkProxy::ProxyType)v.value("ProxyType").toInt());
    setProxyUser(v.value("ProxyUser").toString());
    setProxyPassword(v.value("ProxyPassword").toString());
    setProxyHostName(v.value("ProxyHostName").toString());
    setProxyPort(v.value("ProxyPort").toUInt());

    _storePassword = !password().isEmpty();
}

bool CoreAccount::operator==(const CoreAccount& other) const
{
    return toVariantMap(true) == other.toVariantMap(true);
}

bool CoreAccount::operator!=(const CoreAccount& other) const
{
    return !(*this == other);
}

QDebug operator<<(QDebug dbg, const CoreAccount& acc)
{
    dbg.nospace() << qPrintable(QString("CoreAccount(AccountId:")) << acc.accountId() << qPrintable(QString(", AccountName:"))
                  << acc.accountName() << qPrintable(QString(", Uuid:")) << acc.uuid() << qPrintable(QString(", Internal:"))
                  << acc.isInternal() << qPrintable(QString(", User:")) << acc.user() << qPrintable(QString(", Password:"))
                  << acc.password() << qPrintable(QString(", StorePassword:")) << acc.storePassword() << qPrintable(QString(", HostName:"))
                  << acc.hostName() << qPrintable(QString(", Port:")) << acc.port() << qPrintable(QString(", ProxyType:"))
                  << acc.proxyType() << qPrintable(QString(", ProxyUser:")) << acc.proxyUser() << qPrintable(QString(", ProxyPassword:"))
                  << acc.proxyPassword() << qPrintable(QString(", ProxyHostName:")) << acc.proxyHostName()
                  << qPrintable(QString(", ProxyPort:")) << acc.proxyPort();
    return dbg.space();
}
