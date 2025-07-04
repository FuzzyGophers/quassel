/* SPDX-FileCopyrightText: 2005-2025 Quassel Project <devel@quassel-irc.org> */
/* SPDX-License-Identifier: GPL-2.0-or-later */

/* SPDX-FileCopyrightText: 2005-2025 Quassel Project <devel@quassel-irc.org> */
/* SPDX-License-Identifier: GPL-2.0-or-later */

SELECT COALESCE(SUM(t.type),0)
FROM
  (SELECT DISTINCT TYPE
   FROM backlog
   WHERE bufferid = :bufferid
     AND flags & 32 = 0
     AND flags & 1 = 0
     AND messageid > :lastseenmsgid) t;
