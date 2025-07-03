// SPDX-FileCopyrightText: 2005-2025 Quassel Project <devel@quassel-irc.org>
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

#include "client-export.h"

#include "identity.h"

class ClientCertManager;

class CLIENT_EXPORT CertIdentity : public Identity
{
    Q_OBJECT

public:
    CertIdentity(IdentityId id = 0, QObject* parent = nullptr);
    CertIdentity(const Identity& other, QObject* parent = nullptr);
    CertIdentity(const CertIdentity& other, QObject* parent = nullptr);

    inline bool isDirty() const { return _isDirty; }

    void enableEditSsl(bool enable = true);
    inline const QSslKey& sslKey() const { return _sslKey; }
    inline const QSslCertificate& sslCert() const { return _sslCert; }

    void setSslKey(const QSslKey& key);
    void setSslCert(const QSslCertificate& cert);

public slots:
    void requestUpdateSslSettings();

signals:
    void sslSettingsUpdated();

private slots:
    void markClean();

private:
    ClientCertManager* _certManager{nullptr};
    bool _isDirty{false};
    QSslKey _sslKey;
    QSslCertificate _sslCert;
};

// ========================================
//  ClientCertManager
// ========================================

class ClientCertManager : public CertManager
{
    Q_OBJECT

public:
    ClientCertManager(IdentityId id, CertIdentity* parent)
        : CertManager(id, parent)
        , _certIdentity(parent)
    {}

    inline const QSslKey& sslKey() const override { return _certIdentity->sslKey(); }
    inline const QSslCertificate& sslCert() const override { return _certIdentity->sslCert(); }

public slots:
    void setSslKey(const QByteArray& encoded) override;
    void setSslCert(const QByteArray& encoded) override;

private:
    CertIdentity* _certIdentity;
};

