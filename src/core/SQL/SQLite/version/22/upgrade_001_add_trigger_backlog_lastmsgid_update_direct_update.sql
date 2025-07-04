/* SPDX-FileCopyrightText: 2005-2025 Quassel Project <devel@quassel-irc.org> */
/* SPDX-License-Identifier: GPL-2.0-or-later */

/* SPDX-FileCopyrightText: 2005-2025 Quassel Project <devel@quassel-irc.org> */
/* SPDX-License-Identifier: GPL-2.0-or-later */

CREATE TRIGGER IF NOT EXISTS backlog_lastmsgid_update_trigger_update
AFTER UPDATE
ON backlog
FOR EACH ROW
    BEGIN
        UPDATE buffer
        SET lastmsgid = new.messageid
        WHERE buffer.bufferid = new.bufferid
            AND buffer.lastmsgid < new.messageid;
    END
