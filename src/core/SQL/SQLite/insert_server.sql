/* SPDX-FileCopyrightText: 2005-2025 Quassel Project <devel@quassel-irc.org> */
/* SPDX-License-Identifier: GPL-2.0-or-later */

/* SPDX-FileCopyrightText: 2005-2025 Quassel Project <devel@quassel-irc.org> */
/* SPDX-License-Identifier: GPL-2.0-or-later */

INSERT INTO ircserver (userid, networkid, hostname, port, password, ssl, sslversion, useproxy, proxytype, proxyhost, proxyport, proxyuser, proxypass, sslverify)
VALUES (:userid, :networkid, :hostname, :port, :password, :ssl, :sslversion, :useproxy, :proxytype, :proxyhost, :proxyport, :proxyuser, :proxypass, :sslverify)
