// SPDX-FileCopyrightText: 2005-2025 Quassel Project <devel@quassel-irc.org>
// SPDX-License-Identifier: GPL-2.0-or-later

#include "irctag.h"

uint qHash(const IrcTagKey& key)
{
    QString clientTag;
    if (key.clientTag) {
        clientTag = "+";
    }
    return qHash(QString(clientTag + key.vendor + "/" + key.key));
}

bool operator==(const IrcTagKey& a, const IrcTagKey& b)
{
    return a.vendor == b.vendor && a.key == b.key && a.clientTag == b.clientTag;
}

bool operator<(const IrcTagKey& a, const IrcTagKey& b)
{
    return a.vendor < b.vendor || a.key < b.key || a.clientTag < b.clientTag;
}

QDebug operator<<(QDebug dbg, const IrcTagKey& i)
{
    return dbg << QString(("(clientTag = %1, vendor = %2,key = %3")).arg(i.clientTag).arg(i.vendor).arg(i.key);
}

std::ostream& operator<<(std::ostream& o, const IrcTagKey& i)
{
    std::string result;
    if (i.clientTag)
        result += "+";
    if (!i.vendor.isEmpty()) {
        result += i.vendor.toStdString();
        result += "/";
    }
    result += i.key.toStdString();
    return o << result;
}
