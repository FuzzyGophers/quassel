// SPDX-License-Identifier: GPL-2.0-or-later

#include "printers.h"

#include <QDebug>

namespace {

template<typename T>
void debugOut(const T& value, ::std::ostream* os)
{
    // Just use Qt's own debug print support to print the value into a string
    QString out;
    QDebug dbg(&out);
    dbg.nospace() << value;
    *os << out.toStdString();
}

}  // anon

void PrintTo(const QByteArray& value, std::ostream* os)
{
    debugOut(value, os);
}

void PrintTo(const QDateTime& value, std::ostream* os)
{
    debugOut(value, os);
}

void PrintTo(const QString& value, std::ostream* os)
{
    debugOut(value, os);
}

void PrintTo(const QVariant& value, std::ostream* os)
{
    debugOut(value, os);
}

void PrintTo(const QVariantList& value, std::ostream* os)
{
    debugOut(value, os);
}

void PrintTo(const QVariantMap& value, std::ostream* os)
{
    debugOut(value, os);
}
