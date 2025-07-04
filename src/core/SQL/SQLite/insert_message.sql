/* SPDX-FileCopyrightText: 2005-2025 Quassel Project <devel@quassel-irc.org> */
/* SPDX-License-Identifier: GPL-2.0-or-later */

/* SPDX-FileCopyrightText: 2005-2025 Quassel Project <devel@quassel-irc.org> */
/* SPDX-License-Identifier: GPL-2.0-or-later */

INSERT INTO backlog (time, bufferid, type, flags, senderid, senderprefixes, message)
VALUES (:time, :bufferid, :type, :flags,
	(SELECT senderid FROM sender WHERE sender = :sender AND coalesce(realname, '') = coalesce(:realname, '') AND coalesce(avatarurl, '') = coalesce(:avatarurl, '')),
	:senderprefixes, :message
)
