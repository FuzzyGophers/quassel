/* SPDX-FileCopyrightText: 2005-2025 Quassel Project <devel@quassel-irc.org> */
/* SPDX-License-Identifier: GPL-2.0-or-later */

ALTER TABLE buffer
ALTER COLUMN buffername TYPE TEXT,
ALTER COLUMN buffercname TYPE TEXT,
ALTER COLUMN key TYPE TEXT
