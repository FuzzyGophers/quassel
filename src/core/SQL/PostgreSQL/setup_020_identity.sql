/* SPDX-FileCopyrightText: 2005-2025 Quassel Project <devel@quassel-irc.org> */
/* SPDX-License-Identifier: GPL-2.0-or-later */

CREATE TABLE identity (
       identityid serial PRIMARY KEY,
       userid integer NOT NULL REFERENCES quasseluser (userid) ON DELETE CASCADE,
       identityname TEXT NOT NULL,
       realname TEXT NOT NULL,
       awaynick TEXT,
       awaynickenabled boolean NOT NULL DEFAULT FALSE,
       awayreason TEXT,
       awayreasonenabled boolean NOT NULL DEFAULT FALSE,
       autoawayenabled boolean NOT NULL DEFAULT FALSE,
       autoawaytime integer NOT NULL,
       autoawayreason TEXT,
       autoawayreasonenabled boolean NOT NULL DEFAULT FALSE,
       detachawayenabled boolean NOT NULL DEFAULT FALSE,
       detachawayreason TEXT,
       detachawayreasonenabled boolean NOT NULL DEFAULT FALSE,
       ident TEXT,
       kickreason TEXT,
       partreason TEXT,
       quitreason TEXT,
       sslcert bytea,
       sslkey bytea,
       UNIQUE (userid, identityname)
)
