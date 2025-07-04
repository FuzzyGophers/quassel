/* SPDX-FileCopyrightText: 2005-2025 Quassel Project <devel@quassel-irc.org> */
/* SPDX-License-Identifier: GPL-2.0-or-later */

/* SPDX-FileCopyrightText: 2005-2025 Quassel Project <devel@quassel-irc.org> */
/* SPDX-License-Identifier: GPL-2.0-or-later */

SELECT identityid, identityname, realname, awaynick, awaynickenabled,
       awayreason, awayreasonenabled, autoawayenabled, autoawaytime, autoawayreason, autoawayreasonenabled,
       detachawayenabled, detachawayreason, detachawayreasonenabled, ident, kickreason, partreason, quitreason,
       sslcert, sslkey
FROM identity
WHERE userid = :userid
