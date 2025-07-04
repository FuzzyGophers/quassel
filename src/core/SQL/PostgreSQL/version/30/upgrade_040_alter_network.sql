/* SPDX-FileCopyrightText: 2005-2025 Quassel Project <devel@quassel-irc.org> */
/* SPDX-License-Identifier: GPL-2.0-or-later */

ALTER TABLE network
ALTER COLUMN networkname TYPE TEXT,
ALTER COLUMN encodingcodec TYPE TEXT,
ALTER COLUMN decodingcodec TYPE TEXT,
ALTER COLUMN servercodec TYPE TEXT,
ALTER COLUMN autoidentifyservice TYPE TEXT,
ALTER COLUMN autoidentifypassword TYPE TEXT,
ALTER COLUMN saslaccount TYPE TEXT,
ALTER COLUMN saslpassword TYPE TEXT,
ALTER COLUMN usermode TYPE TEXT,
ALTER COLUMN awaymessage TYPE TEXT
