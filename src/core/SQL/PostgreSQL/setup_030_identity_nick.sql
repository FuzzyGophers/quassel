/* SPDX-FileCopyrightText: 2005-2025 Quassel Project <devel@quassel-irc.org> */
/* SPDX-License-Identifier: GPL-2.0-or-later */

CREATE TABLE identity_nick (
       nickid serial PRIMARY KEY,
       identityid integer NOT NULL REFERENCES identity (identityid) ON DELETE CASCADE,
       nick TEXT NOT NULL,
       UNIQUE (identityid, nick)
)
