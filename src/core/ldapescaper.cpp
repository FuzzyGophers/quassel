// SPDX-License-Identifier: GPL-2.0-or-later

#include "ldapescaper.h"

QString LdapEscaper::escapeQuery(const QString& filter)
{
    QString result;
    for (const auto character : filter) {
			if (character.unicode() > 0x7F ||
            character == '*' ||
            character == '(' ||
            character == ')' ||
            character == '\\' ||
            character == '\0') {
            for (uint8_t byte: QString(character).toUtf8()) {
                result += "\\";
                result += QString::number(byte, 16).rightJustified(2, '0');
            }
        } else {
            result += character;
        }
    }
    return result;
}
