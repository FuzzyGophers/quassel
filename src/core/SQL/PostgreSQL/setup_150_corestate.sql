/* SPDX-FileCopyrightText: 2005-2025 Quassel Project <devel@quassel-irc.org> */
/* SPDX-License-Identifier: GPL-2.0-or-later */

CREATE TABLE core_state (
    key TEXT NOT NULL,
    value bytea,
    PRIMARY KEY (key)
)
