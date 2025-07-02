// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

#include "client-export.h"

#include <QMap>

#include "ignorelistmanager.h"

class CLIENT_EXPORT ClientIgnoreListManager : public IgnoreListManager
{
    Q_OBJECT

public:
    explicit ClientIgnoreListManager(QObject* parent = nullptr);

    //! Fetch all matching ignore rules for a given hostmask
    /** \param hostmask The hostmask of the user
     * \param network The network name
     * \param channel The channel name
     * \return Returns a QMap with the rule as key and a bool, representing if the rule is enabled or not, as value
     */
    QMap<QString, bool> matchingRulesForHostmask(const QString& hostmask, const QString& network, const QString& channel) const;

signals:
    void ignoreListChanged();

private:
    // matches an ignore rule against a given string
    bool pureMatch(const IgnoreListItem& item, const QString& string) const;
};
