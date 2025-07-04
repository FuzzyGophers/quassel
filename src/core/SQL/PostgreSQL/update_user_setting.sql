/* SPDX-FileCopyrightText: 2005-2025 Quassel Project <devel@quassel-irc.org> */
/* SPDX-License-Identifier: GPL-2.0-or-later */

UPDATE user_setting
SET settingvalue = :settingvalue
WHERE userid = :userid AND settingname = :settingname
