/* SPDX-FileCopyrightText: 2005-2025 Quassel Project <devel@quassel-irc.org> */
/* SPDX-License-Identifier: GPL-2.0-or-later */

/* SPDX-FileCopyrightText: 2005-2025 Quassel Project <devel@quassel-irc.org> */
/* SPDX-License-Identifier: GPL-2.0-or-later */

UPDATE ircserver
SET ssl = length(replace(replace(replace(ssl,'true','1'), 'false', '0'), '0', '')),
    useproxy = length(replace(replace(replace(useproxy,'true','1'), 'false', '0'), '0', ''))
