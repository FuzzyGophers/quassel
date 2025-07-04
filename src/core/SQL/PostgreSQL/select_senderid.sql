/* SPDX-FileCopyrightText: 2005-2025 Quassel Project <devel@quassel-irc.org> */
/* SPDX-License-Identifier: GPL-2.0-or-later */

SELECT senderid
FROM sender
WHERE sender = $1 AND coalesce(realname, '') = coalesce($2, '') AND coalesce(avatarurl, '') = coalesce($3, '')
