/* SPDX-FileCopyrightText: 2005-2025 Quassel Project <devel@quassel-irc.org> */
/* SPDX-License-Identifier: GPL-2.0-or-later */

/* SPDX-FileCopyrightText: 2005-2025 Quassel Project <devel@quassel-irc.org> */
/* SPDX-License-Identifier: GPL-2.0-or-later */

CREATE TABLE buffer (
	bufferid INTEGER NOT NULL PRIMARY KEY AUTOINCREMENT,
	userid INTEGER NOT NULL,
	groupid INTEGER,
	networkid INTEGER NOT NULL,
	buffername TEXT NOT NULL,
	buffercname TEXT NOT NULL, -- CANONICAL BUFFER NAME (lowercase version)
	buffertype INTEGER NOT NULL DEFAULT 0,
	lastseenmsgid INTEGER NOT NULL DEFAULT 0,
	key TEXT,
	joined INTEGER NOT NULL DEFAULT 0 -- BOOL
)
