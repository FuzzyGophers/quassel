// SPDX-FileCopyrightText: 2005-2025 Quassel Project <devel@quassel-irc.org>
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

#include "common-export.h"

#include <ostream>
#include <utility>

#include <QDebug>
#include <QString>

struct COMMON_EXPORT IrcTagKey
{
    QString vendor;
    QString key;
    bool clientTag;

    explicit IrcTagKey(QString vendor, QString key, bool clientTag = false)
        : vendor(std::move(vendor))
        , key(std::move(key))
        , clientTag(clientTag)
    {
    }

    explicit IrcTagKey(QString key = {})
        : vendor(QString{})
        , key(std::move(key))
        , clientTag(false)
    {
    }

    friend COMMON_EXPORT uint qHash(const IrcTagKey& key);
    friend COMMON_EXPORT bool operator==(const IrcTagKey& a, const IrcTagKey& b);
    friend COMMON_EXPORT bool operator<(const IrcTagKey& a, const IrcTagKey& b);
    friend COMMON_EXPORT QDebug operator<<(QDebug dbg, const IrcTagKey& i);
    friend COMMON_EXPORT std::ostream& operator<<(std::ostream& o, const IrcTagKey& i);
};
