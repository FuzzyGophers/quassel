// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

#include "core-export.h"

#include "identity.h"

#include <QSslCertificate>
#include <QSslKey>

class SignalProxy;

// ========================================
//  CoreCertManager
// ========================================
class CoreIdentity;
class CORE_EXPORT CoreCertManager : public CertManager
{
    Q_OBJECT

public:
    CoreCertManager(CoreIdentity* identity);

    const QSslKey& sslKey() const override;
    const QSslCertificate& sslCert() const override;

public slots:
    void setSslKey(const QByteArray& encoded) override;
    void setSslCert(const QByteArray& encoded) override;

    void setId(IdentityId id);

private:
    CoreIdentity* _identity{nullptr};
};

// =========================================
//  CoreIdentity
// =========================================
class CORE_EXPORT CoreIdentity : public Identity
{
    Q_OBJECT

public:
    CoreIdentity(IdentityId id, QObject* parent = nullptr);
    CoreIdentity(const Identity& other, QObject* parent = nullptr);
    CoreIdentity(const CoreIdentity& other, QObject* parent = nullptr);

    void synchronize(SignalProxy* proxy);

    inline const QSslKey& sslKey() const { return _sslKey; }
    inline void setSslKey(const QSslKey& key) { _sslKey = key; }
    void setSslKey(const QByteArray& encoded);
    inline const QSslCertificate& sslCert() const { return _sslCert; }
    inline void setSslCert(const QSslCertificate& cert) { _sslCert = cert; }
    void setSslCert(const QByteArray& encoded);

private:
    QSslKey _sslKey;
    QSslCertificate _sslCert;

    CoreCertManager _certManager;
};

inline const QSslKey& CoreCertManager::sslKey() const
{
    return _identity->sslKey();
}

inline const QSslCertificate& CoreCertManager::sslCert() const
{
    return _identity->sslCert();
}
