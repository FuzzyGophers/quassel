/* SPDX-FileCopyrightText: 2005-2025 Quassel Project <devel@quassel-irc.org> */
/* SPDX-License-Identifier: GPL-2.0-or-later */

CREATE TABLE user_setting (
    userid integer NOT NULL REFERENCES quasseluser (userid) ON DELETE CASCADE,
    settingname TEXT NOT NULL,
    settingvalue bytea,
    PRIMARY KEY (userid, settingname)
)
