// SPDX-FileCopyrightText: 2005-2025 Quassel Project <devel@quassel-irc.org>
// SPDX-License-Identifier: GPL-2.0-or-later

#include "coreidentity.h"

#include "signalproxy.h"

CoreIdentity::CoreIdentity(IdentityId id, QObject* parent)
    : Identity(id, parent)
    , _certManager(this)
{
    connect(this, &Identity::idSet, &_certManager, &CoreCertManager::setId);
    connect(&_certManager, &SyncableObject::updated, this, &SyncableObject::updated);
}

CoreIdentity::CoreIdentity(const Identity& other, QObject* parent)
    : Identity(other, parent)
    , _certManager(this)
{
    connect(this, &Identity::idSet, &_certManager, &CoreCertManager::setId);
    connect(&_certManager, &SyncableObject::updated, this, &SyncableObject::updated);
}

CoreIdentity::CoreIdentity(const CoreIdentity& other, QObject* parent)
    : Identity(other, parent)
    , _sslKey(other._sslKey)
    , _sslCert(other._sslCert)
    , _certManager(this)
{
    connect(this, &Identity::idSet, &_certManager, &CoreCertManager::setId);
    connect(&_certManager, &SyncableObject::updated, this, &SyncableObject::updated);
}

void CoreIdentity::synchronize(SignalProxy* proxy)
{
    proxy->synchronize(this);
    proxy->synchronize(&_certManager);
}

void CoreIdentity::setSslKey(const QByteArray& encoded)
{
    QSslKey key(encoded, QSsl::Rsa);
    if (key.isNull())
        key = QSslKey(encoded, QSsl::Ec);
    if (key.isNull())
        key = QSslKey(encoded, QSsl::Dsa);
    setSslKey(key);
}

void CoreIdentity::setSslCert(const QByteArray& encoded)
{
    setSslCert(QSslCertificate(encoded));
}

// ========================================
//  CoreCertManager
// ========================================

CoreCertManager::CoreCertManager(CoreIdentity* identity)
    : CertManager(identity->id())
    , _identity(identity)
{
    setAllowClientUpdates(true);
}

void CoreCertManager::setId(IdentityId id)
{
    setObjectName(QString::number(id.toInt()));
}

void CoreCertManager::setSslKey(const QByteArray& encoded)
{
    _identity->setSslKey(encoded);
    CertManager::setSslKey(encoded);
}

void CoreCertManager::setSslCert(const QByteArray& encoded)
{
    _identity->setSslCert(encoded);
    CertManager::setSslCert(encoded);
}
