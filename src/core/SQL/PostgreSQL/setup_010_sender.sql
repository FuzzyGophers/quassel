/* SPDX-FileCopyrightText: 2005-2025 Quassel Project <devel@quassel-irc.org> */
/* SPDX-License-Identifier: GPL-2.0-or-later */

CREATE TABLE sender ( -- THE SENDER OF IRC MESSAGES
       senderid bigserial NOT NULL PRIMARY KEY,
       sender TEXT NOT NULL,
       realname TEXT,
       avatarurl TEXT
);
