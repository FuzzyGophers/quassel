/* SPDX-FileCopyrightText: 2005-2025 Quassel Project <devel@quassel-irc.org> */
/* SPDX-License-Identifier: GPL-2.0-or-later */

UPDATE identity
SET    identityname = :identityname,
       realname = :realname,
       awaynick = :awaynick,
       awaynickenabled = :awaynickenabled,
       awayreason = :awayreason,
       awayreasonenabled = :awayreasonenabled,
       autoawayenabled = :autoawayenabled,
       autoawaytime = :autoawaytime,
       autoawayreason = :autoawayreason,
       autoawayreasonenabled = :autoawayreasonenabled,
       detachawayenabled = :detachawayenabled,
       detachawayreason = :detachawayreason,
       detachawayreasonenabled = :detachawayreasonenabled,
       ident = :ident,
       kickreason = :kickreason,
       partreason = :partreason,
       quitreason = :quitreason,
       sslcert = :sslcert,
       sslkey = :sslkey
WHERE  identityid = :identityid
