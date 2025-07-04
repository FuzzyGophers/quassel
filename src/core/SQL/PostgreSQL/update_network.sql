/* SPDX-FileCopyrightText: 2005-2025 Quassel Project <devel@quassel-irc.org> */
/* SPDX-License-Identifier: GPL-2.0-or-later */

UPDATE network SET
networkname = :networkname,
identityid = :identityid,
servercodec = :servercodec,
encodingcodec = :encodingcodec,
decodingcodec = :decodingcodec,
userandomserver = :userandomserver,
perform = :perform,
useautoidentify = :useautoidentify,
autoidentifyservice = :autoidentifyservice,
autoidentifypassword = :autoidentifypassword,
useautoreconnect = :useautoreconnect,
autoreconnectinterval = :autoreconnectinterval,
autoreconnectretries = :autoreconnectretries,
unlimitedconnectretries = :unlimitedconnectretries,
usecustomessagerate = :usecustomessagerate,
messagerateburstsize = :messagerateburstsize,
messageratedelay = :messageratedelay,
unlimitedmessagerate = :unlimitedmessagerate,
rejoinchannels = :rejoinchannels,
usesasl = :usesasl,
saslaccount = :saslaccount,
saslpassword = :saslpassword,
skipcaps = :skipcaps
WHERE userid = :userid AND networkid = :networkid

