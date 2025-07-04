/* SPDX-FileCopyrightText: 2005-2025 Quassel Project <devel@quassel-irc.org> */
/* SPDX-License-Identifier: GPL-2.0-or-later */

/* SPDX-FileCopyrightText: 2005-2025 Quassel Project <devel@quassel-irc.org> */
/* SPDX-License-Identifier: GPL-2.0-or-later */

UPDATE network
SET userandomserver = length(replace(replace(replace(userandomserver,'true','1'), 'false', '0'), '0', '')),
    useautoidentify = length(replace(replace(replace(useautoidentify,'true','1'), 'false', '0'), '0', '')),
    useautoreconnect = length(replace(replace(replace(useautoreconnect,'true','1'), 'false', '0'), '0', '')),
    unlimitedconnectretries = length(replace(replace(replace(unlimitedconnectretries,'true','1'), 'false', '0'), '0', '')),
    rejoinchannels = length(replace(replace(replace(rejoinchannels,'true','1'), 'false', '0'), '0', '')),
    connected = length(replace(replace(replace(connected,'true','1'), 'false', '0'), '0', ''))
