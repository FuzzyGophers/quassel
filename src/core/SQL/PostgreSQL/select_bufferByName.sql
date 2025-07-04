/* SPDX-FileCopyrightText: 2005-2025 Quassel Project <devel@quassel-irc.org> */
/* SPDX-License-Identifier: GPL-2.0-or-later */

SELECT bufferid, buffertype, groupid
FROM buffer
WHERE networkid = :networkid AND userid = :userid AND buffercname = :buffercname
