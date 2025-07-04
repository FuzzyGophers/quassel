/* SPDX-FileCopyrightText: 2005-2025 Quassel Project <devel@quassel-irc.org> */
/* SPDX-License-Identifier: GPL-2.0-or-later */

UPDATE network
SET awaymessage = :awaymsg
WHERE userid = :userid AND networkid = :networkid
