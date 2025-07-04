/* SPDX-FileCopyrightText: 2005-2025 Quassel Project <devel@quassel-irc.org> */
/* SPDX-License-Identifier: GPL-2.0-or-later */

/* SPDX-FileCopyrightText: 2005-2025 Quassel Project <devel@quassel-irc.org> */
/* SPDX-License-Identifier: GPL-2.0-or-later */

CREATE TABLE backlog (
	messageid INTEGER NOT NULL PRIMARY KEY AUTOINCREMENT,
	time INTEGER NOT NULL,
	bufferid INTEGER NOT NULL,
	type INTEGER NOT NULL,
	flags INTEGER NOT NULL,
	senderid INTEGER NOT NULL,
	senderprefixes TEXT,
	message TEXT
)
