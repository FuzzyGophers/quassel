// SPDX-FileCopyrightText: 2005-2025 Quassel Project <devel@quassel-irc.org>
// SPDX-License-Identifier: GPL-2.0-or-later

/* This file contains an implementation of an LDAP Authenticator, as an example
 * of what a custom external auth provider could do.
 *
 * It's based off of this pull request for quassel by abustany:
 * https://github.com/quassel/quassel/pull/4/
 *
 */

#pragma once

#include "authenticator.h"
#include "core.h"

// Link against LDAP.
/* We should use openldap on windows if at all possible, rather than trying to
 * write some kind of compatibility routine.
#ifdef Q_CC_MSVC
#include <windows.h>
#include <winldap.h>
#else*/
#include <ldap.h>
// #endif

// Default LDAP server port.
constexpr int DEFAULT_LDAP_PORT = 389;

class LdapAuthenticator : public Authenticator
{
    Q_OBJECT

public:
    LdapAuthenticator(QObject* parent = nullptr);
    ~LdapAuthenticator() override;

public slots:
    /* General */
    bool isAvailable() const override;
    QString backendId() const override;
    QString displayName() const override;
    QString description() const override;
    QVariantList setupData() const override;

    bool canChangePassword() const override { return false; }

    bool setup(const QVariantMap& settings, const QProcessEnvironment& environment, bool loadFromEnvironment) override;
    State init(const QVariantMap& settings, const QProcessEnvironment& environment, bool loadFromEnvironment) override;
    UserId validateUser(const QString& user, const QString& password) override;

protected:
    void setAuthProperties(const QVariantMap& properties, const QProcessEnvironment& environment, bool loadFromEnvironment);
    bool ldapConnect();
    void ldapDisconnect();
    bool ldapAuth(const QString& username, const QString& password);

    // Protected methods for retrieving info about the LDAP connection.
    QString hostName() const { return _hostName; }
    int port() const { return _port; }
    QString bindDN() const { return _bindDN; }
    QString baseDN() const { return _baseDN; }

private:
    QString _hostName;
    int _port;
    QString _bindDN;
    QString _baseDN;
    QString _filter;
    QString _bindPassword;
    QString _uidAttribute;

    // The actual connection object.
    LDAP* _connection{nullptr};
};
