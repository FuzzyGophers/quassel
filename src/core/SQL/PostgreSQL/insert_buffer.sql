/* SPDX-FileCopyrightText: 2005-2025 Quassel Project <devel@quassel-irc.org> */
/* SPDX-License-Identifier: GPL-2.0-or-later */

INSERT INTO buffer (userid, networkid, buffername, buffercname, buffertype, joined)
VALUES (:userid, :networkid, :buffername, :buffercname, :buffertype, :joined)
RETURNING bufferid
