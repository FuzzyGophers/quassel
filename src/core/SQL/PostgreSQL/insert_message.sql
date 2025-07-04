/* SPDX-FileCopyrightText: 2005-2025 Quassel Project <devel@quassel-irc.org> */
/* SPDX-License-Identifier: GPL-2.0-or-later */

INSERT INTO backlog (time, bufferid, type, flags, senderid, senderprefixes, message)
VALUES ($1, $2, $3, $4, $5, $6, $7)
RETURNING messageid
