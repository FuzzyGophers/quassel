// SPDX-FileCopyrightText: 2005-2025 Quassel Project <devel@quassel-irc.org>
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

#include <QObject>
#include <QProcessEnvironment>
#include <QString>
#include <QStringList>
#include <QVariant>

#include "types.h"

class Authenticator : public QObject
{
    Q_OBJECT

public:
    using QObject::QObject;
    ~Authenticator() override = default;

    enum State
    {
        IsReady,      // ready to go
        NeedsSetup,   // need basic setup (ask the user for input)
        NotAvailable  // remove the authenticator backend from the list of available authenticators.
    };

public slots:
    // General

    //! Check if the authenticator type is available.
    /** An authenticator subclass should return true if it can be successfully used, i.e. if all
     *  prerequisites are in place.
     * \return True if and only if the authenticator class can be successfully used.
     */
    virtual bool isAvailable() const = 0;

    //! Returns the identifier of the authenticator backend
    /** \return A string that can be used by the client to identify the authenticator backend */
    virtual QString backendId() const = 0;

    //! Returns the display name of the authenticator backend
    /** \return A string that can be used by the client to name the authenticator backend */
    virtual QString displayName() const = 0;

    //! Returns a description of this authenticator backend
    /** \return A string that can be displayed by the client to describe the authenticator */
    virtual QString description() const = 0;

    //! Returns data required to configure the authenticator backend
    /**
     * A list of flattened triples for each field: {key, translated field name, default value}
     * The default value's type determines the kind of input widget to be shown
     * (int -> QSpinBox; QString -> QLineEdit)
     * \return A list of triples defining the data to be shown in the configuration dialog
     */
    virtual QVariantList setupData() const = 0;

    //! Checks if the authenticator allows manual password changes from inside quassel.
    virtual bool canChangePassword() const = 0;

    //! Setup the authenticator provider.
    /** This prepares the authenticator provider (e.g. create tables, etc.) for use within Quassel.
     *  \param settings   Hostname, port, username, password, ...
     *  \return True if and only if the authenticator provider was initialized successfully.
     */
    virtual bool setup(const QVariantMap& settings = QVariantMap(),
                       const QProcessEnvironment& environment = {},
                       bool loadFromEnvironment = false)
        = 0;

    //! Initialize the authenticator provider
    /** \param settings   Hostname, port, username, password, ...
     *  \return the State the authenticator backend is now in (see authenticator::State)
     */
    virtual State init(const QVariantMap& settings = QVariantMap(),
                       const QProcessEnvironment& environment = {},
                       bool loadFromEnvironment = false)
        = 0;

    //! Validate a username with a given password.
    /** \param user     The username to validate
     *  \param password The user's alleged password
     *  \return A valid UserId if the password matches the username; 0 else
     */
    virtual UserId validateUser(const QString& user, const QString& password) = 0;
};
