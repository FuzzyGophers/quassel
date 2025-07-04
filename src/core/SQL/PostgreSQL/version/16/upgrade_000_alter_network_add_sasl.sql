/* SPDX-FileCopyrightText: 2005-2025 Quassel Project <devel@quassel-irc.org> */
/* SPDX-License-Identifier: GPL-2.0-or-later */

ALTER TABLE network
ADD COLUMN usesasl boolean NOT NULL DEFAULT FALSE,
ADD COLUMN saslaccount varchar(128),
ADD COLUMN saslpassword varchar(128)
