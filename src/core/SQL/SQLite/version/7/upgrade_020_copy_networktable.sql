/* SPDX-FileCopyrightText: 2005-2025 Quassel Project <devel@quassel-irc.org> */
/* SPDX-License-Identifier: GPL-2.0-or-later */

/* SPDX-FileCopyrightText: 2005-2025 Quassel Project <devel@quassel-irc.org> */
/* SPDX-License-Identifier: GPL-2.0-or-later */

INSERT INTO network (networkid, userid, networkname, identityid, encodingcodec, decodingcodec, userandomserver, perform, useautoidentify, autoidentifyservice, autoidentifypassword, useautoreconnect, autoreconnectinterval, autoreconnectretries, rejoinchannels)
SELECT networkid, userid, networkname, identityid, encodingcodec, decodingcodec, userandomserver, perform, useautoidentify, autoidentifyservice, autoidentifypassword, useautoreconnect, autoreconnectinterval, autoreconnectretries, rejoinchannels FROM networkold;
