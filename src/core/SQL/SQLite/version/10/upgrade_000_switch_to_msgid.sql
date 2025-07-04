/* SPDX-FileCopyrightText: 2005-2025 Quassel Project <devel@quassel-irc.org> */
/* SPDX-License-Identifier: GPL-2.0-or-later */

/* SPDX-FileCopyrightText: 2005-2025 Quassel Project <devel@quassel-irc.org> */
/* SPDX-License-Identifier: GPL-2.0-or-later */

UPDATE buffer
SET lastseen = (SELECT messageid FROM backlog WHERE backlog.bufferid = buffer.bufferid AND backlog.time = buffer.lastseen UNION SELECT 0 ORDER BY messageid DESC LIMIT 1)
WHERE lastseen != 0
