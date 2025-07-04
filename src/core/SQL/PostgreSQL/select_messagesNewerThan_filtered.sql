/* SPDX-FileCopyrightText: 2005-2025 Quassel Project <devel@quassel-irc.org> */
/* SPDX-License-Identifier: GPL-2.0-or-later */

SELECT messageid, time, type, flags, sender, senderprefixes, realname, avatarurl, message
FROM backlog
JOIN sender ON backlog.senderid = sender.senderid
WHERE backlog.messageid >= :first
    AND backlog.messageid <= (SELECT buffer.lastmsgid FROM buffer WHERE buffer.bufferid = :buffer)
    AND bufferid = :buffer
    AND (:type <= 0 OR backlog.type & :type != 0)
    AND (:flags <= 0 OR backlog.flags & :flags != 0)
ORDER BY messageid DESC
LIMIT :limit
