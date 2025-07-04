/* SPDX-FileCopyrightText: 2005-2025 Quassel Project <devel@quassel-irc.org> */
/* SPDX-License-Identifier: GPL-2.0-or-later */

CREATE TRIGGER backlog_lastmsgid_update_trigger
AFTER INSERT OR UPDATE
ON public.backlog
FOR EACH ROW
EXECUTE PROCEDURE public.backlog_lastmsgid_update();
