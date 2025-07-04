/* SPDX-FileCopyrightText: 2005-2025 Quassel Project <devel@quassel-irc.org> */
/* SPDX-License-Identifier: GPL-2.0-or-later */

ALTER TABLE identity
ALTER COLUMN identityname TYPE TEXT,
ALTER COLUMN realname TYPE TEXT,
ALTER COLUMN awaynick TYPE TEXT,
ALTER COLUMN awayreason TYPE TEXT,
ALTER COLUMN autoawayreason TYPE TEXT,
ALTER COLUMN detachawayreason TYPE TEXT,
ALTER COLUMN ident TYPE TEXT,
ALTER COLUMN kickreason TYPE TEXT,
ALTER COLUMN partreason TYPE TEXT,
ALTER COLUMN quitreason TYPE TEXT
