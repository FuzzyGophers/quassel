// SPDX-FileCopyrightText: 2005-2025 Quassel Project <devel@quassel-irc.org>
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

#include "core-export.h"

#include <QString>

namespace LdapEscaper {

/**
 * Escapes a filter or query according to RFC 4515
 *
 * @note This does not handle escaping distinguished names (dn).
 * @param filter
 * @return
 */
CORE_EXPORT QString escapeQuery(const QString& query);

}  // namespace LdapEscaper
