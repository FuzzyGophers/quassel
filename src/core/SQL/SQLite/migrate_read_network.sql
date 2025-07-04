/* SPDX-FileCopyrightText: 2005-2025 Quassel Project <devel@quassel-irc.org> */
/* SPDX-License-Identifier: GPL-2.0-or-later */

/* SPDX-FileCopyrightText: 2005-2025 Quassel Project <devel@quassel-irc.org> */
/* SPDX-License-Identifier: GPL-2.0-or-later */

SELECT networkid, userid, networkname, identityid, encodingcodec, decodingcodec, servercodec,
       userandomserver, perform, useautoidentify, autoidentifyservice, autoidentifypassword,
       useautoreconnect, autoreconnectinterval, autoreconnectretries, unlimitedconnectretries,
       rejoinchannels, connected, usermode, awaymessage, attachperform, detachperform,
       usesasl, saslaccount, saslpassword, usecustomessagerate, messagerateburstsize,
       messageratedelay, unlimitedmessagerate, skipcaps
FROM network
