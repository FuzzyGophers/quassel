// SPDX-License-Identifier: GPL-2.0-or-later

#include "mac_utils.h"

#include <QVarLengthArray>

QString CFStringToQString(CFStringRef str)
{
    if (!str)
        return QString();

    CFIndex length = CFStringGetLength(str);
    const UniChar* chars = CFStringGetCharactersPtr(str);
    if (chars)
        return QString(reinterpret_cast<const QChar*>(chars), length);

    QVarLengthArray<UniChar> buffer(length);
    CFStringGetCharacters(str, CFRangeMake(0, length), buffer.data());
    return QString(reinterpret_cast<const QChar*>(buffer.constData()), length);
}
