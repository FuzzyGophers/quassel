/* SPDX-FileCopyrightText: 2005-2025 Quassel Project <devel@quassel-irc.org> */
/* SPDX-License-Identifier: GPL-2.0-or-later */

/* SPDX-FileCopyrightText: 2005-2025 Quassel Project <devel@quassel-irc.org> */
/* SPDX-License-Identifier: GPL-2.0-or-later */

INSERT INTO buffer_new (
	bufferid, 
	userid, 
	groupid, 
	networkid, 
	buffername, 
	buffercname, 
	buffertype, 
	lastmsgid, 
	lastseenmsgid,
	markerlinemsgid,
	key,
	joined
)
SELECT 
	bufferid,
	userid,
	groupid,
	networkid,
	buffername,
	buffercname,
	buffertype,
	lastmsgid,
	lastseenmsgid,
	markerlinemsgid,
	key,
	joined
FROM buffer;
