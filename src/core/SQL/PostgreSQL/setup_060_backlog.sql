/* SPDX-FileCopyrightText: 2005-2025 Quassel Project <devel@quassel-irc.org> */
/* SPDX-License-Identifier: GPL-2.0-or-later */

CREATE TABLE backlog (
	messageid bigserial PRIMARY KEY,
	time timestamp NOT NULL,
	bufferid integer NOT NULL REFERENCES buffer (bufferid) ON DELETE CASCADE,
	type integer NOT NULL,
	flags integer NOT NULL,
	senderid bigint NOT NULL REFERENCES sender (senderid) ON DELETE SET NULL,
	senderprefixes TEXT,
	message TEXT
)
