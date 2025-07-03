// SPDX-FileCopyrightText: 2005-2025 Quassel Project <devel@quassel-irc.org>
// SPDX-License-Identifier: GPL-2.0-or-later

#include "sqlauthenticator.h"

#include "core.h"
#include "network.h"
#include "quassel.h"

SqlAuthenticator::SqlAuthenticator(QObject* parent)
    : Authenticator(parent)
{}

bool SqlAuthenticator::isAvailable() const
{
    // FIXME: probably this should query the current storage (see the ::init routine too).
    return true;
}

QString SqlAuthenticator::backendId() const
{
    // We identify the backend to use for the monolithic core by this identifier.
    // so only change this string if you _really_ have to and make sure the core
    // setup for the mono client still works ;)
    return QString("Database");
}

QString SqlAuthenticator::displayName() const
{
    return tr("Database");
}

QString SqlAuthenticator::description() const
{
    return tr("Do not authenticate against any remote service, but instead save a hashed and salted password "
              "in the database selected in the next step.");
}

UserId SqlAuthenticator::validateUser(const QString& user, const QString& password)
{
    return Core::validateUser(user, password);
}

bool SqlAuthenticator::setup(const QVariantMap& settings, const QProcessEnvironment& environment, bool loadFromEnvironment)
{
    Q_UNUSED(settings)
    Q_UNUSED(environment)
    Q_UNUSED(loadFromEnvironment)
    return true;
}

Authenticator::State SqlAuthenticator::init(const QVariantMap& settings, const QProcessEnvironment& environment, bool loadFromEnvironment)
{
    Q_UNUSED(settings)
    Q_UNUSED(environment)
    Q_UNUSED(loadFromEnvironment)

    // TODO: FIXME: this should check if the storage provider is ready, but I don't
    // know if there's an exposed way to do that at the moment.

    qInfo() << qPrintable(backendId()) << "authenticator is ready.";
    return IsReady;
}
