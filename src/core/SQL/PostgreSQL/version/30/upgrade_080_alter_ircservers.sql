/* SPDX-FileCopyrightText: 2005-2025 Quassel Project <devel@quassel-irc.org> */
/* SPDX-License-Identifier: GPL-2.0-or-later */

ALTER TABLE ircserver
ALTER COLUMN password TYPE TEXT,
ALTER COLUMN hostname TYPE TEXT,
ALTER COLUMN proxyhost TYPE TEXT,
ALTER COLUMN proxyuser TYPE TEXT,
ALTER COLUMN proxypass TYPE TEXT
