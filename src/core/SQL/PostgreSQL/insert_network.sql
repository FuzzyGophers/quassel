/* SPDX-FileCopyrightText: 2005-2025 Quassel Project <devel@quassel-irc.org> */
/* SPDX-License-Identifier: GPL-2.0-or-later */

INSERT INTO network (userid, networkname, identityid, servercodec, encodingcodec, decodingcodec,
                     userandomserver, perform, useautoidentify, autoidentifyservice,
                     autoidentifypassword, useautoreconnect, autoreconnectinterval,
                     autoreconnectretries, unlimitedconnectretries, rejoinchannels, usesasl,
                     saslaccount, saslpassword, usecustomessagerate, messagerateburstsize,
                     messageratedelay, unlimitedmessagerate, skipcaps)
VALUES (:userid, :networkname, :identityid, :servercodec, :encodingcodec, :decodingcodec,
        :userandomserver, :perform, :useautoidentify, :autoidentifyservice, :autoidentifypassword,
        :useautoreconnect, :autoreconnectinterval, :autoreconnectretries, :unlimitedconnectretries,
        :rejoinchannels, :usesasl, :saslaccount, :saslpassword, :usecustomessagerate,
        :messagerateburstsize, :messageratedelay, :unlimitedmessagerate, :skipcaps)
RETURNING networkid
