/* SPDX-FileCopyrightText: 2005-2025 Quassel Project <devel@quassel-irc.org> */
/* SPDX-License-Identifier: GPL-2.0-or-later */

/* SPDX-FileCopyrightText: 2005-2025 Quassel Project <devel@quassel-irc.org> */
/* SPDX-License-Identifier: GPL-2.0-or-later */

CREATE TABLE ircserver (
    serverid INTEGER NOT NULL PRIMARY KEY AUTOINCREMENT,
    userid INTEGER NOT NULL,
    networkid INTEGER NOT NULL,
    hostname TEXT NOT NULL,
    port INTEGER NOT NULL DEFAULT 6667,
    password TEXT,
    ssl INTEGER NOT NULL DEFAULT 0 -- BOOL 
)
