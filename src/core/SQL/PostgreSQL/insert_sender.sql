/* SPDX-FileCopyrightText: 2005-2025 Quassel Project <devel@quassel-irc.org> */
/* SPDX-License-Identifier: GPL-2.0-or-later */

INSERT INTO sender (sender, realname, avatarurl)
VALUES ($1, $2, $3)
RETURNING senderid
