// SPDX-FileCopyrightText: 2005-2025 Quassel Project <devel@quassel-irc.org>
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

#include "authenticator.h"

class SqlAuthenticator : public Authenticator
{
    Q_OBJECT

public:
    SqlAuthenticator(QObject* parent = nullptr);

public slots:
    /* General */
    bool isAvailable() const override;
    QString backendId() const override;
    QString displayName() const override;
    QString description() const override;
    inline QVariantList setupData() const override { return {}; }

    inline bool canChangePassword() const override { return true; }

    bool setup(const QVariantMap& settings, const QProcessEnvironment& environment, bool loadFromEnvironment) override;
    State init(const QVariantMap& settings, const QProcessEnvironment& environment, bool loadFromEnvironment) override;
    UserId validateUser(const QString& user, const QString& password) override;

    /* User handling */
    // virtual UserId getUserId(const QString &username);
};
