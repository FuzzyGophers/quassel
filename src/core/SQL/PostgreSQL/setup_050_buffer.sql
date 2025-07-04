/* SPDX-FileCopyrightText: 2005-2025 Quassel Project <devel@quassel-irc.org> */
/* SPDX-License-Identifier: GPL-2.0-or-later */

create TABLE buffer (
	bufferid serial PRIMARY KEY,
	userid integer NOT NULL REFERENCES quasseluser (userid) ON DELETE CASCADE,
	groupid integer,
	networkid integer NOT NULL REFERENCES network (networkid) ON DELETE CASCADE,
	buffername TEXT NOT NULL,
	buffercname TEXT NOT NULL, -- CANONICAL BUFFER NAME (lowercase version)
	buffertype integer NOT NULL DEFAULT 0,
	lastmsgid bigint NOT NULL DEFAULT 0,
	lastseenmsgid bigint NOT NULL DEFAULT 0,
	markerlinemsgid bigint NOT NULL DEFAULT 0,
	bufferactivity integer NOT NULL DEFAULT 0,
	highlightcount integer NOT NULL DEFAULT 0,
	key TEXT,
	joined boolean NOT NULL DEFAULT FALSE, -- BOOL
	cipher TEXT,
	UNIQUE(userid, networkid, buffercname),
	CHECK (buffer.lastseenmsgid <= buffer.lastmsgid)
)
