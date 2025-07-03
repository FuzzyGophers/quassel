// SPDX-FileCopyrightText: 2005-2025 Quassel Project <devel@quassel-irc.org>
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

#include "irctag.h"

/**
 * This namespace contains commonly used message tags, similar to the IrcCaps
 * namespace used for IRCv3 capabilities.
 */
namespace IrcTags {
/**
 * Services account status with user messages
 *
 * https://ircv3.net/specs/extensions/account-tag-3.2
 */
const IrcTagKey ACCOUNT = IrcTagKey{"", "account", false};

/**
 * Server time for messages.
 *
 * https://ircv3.net/specs/extensions/server-time-3.2.html
 */
const IrcTagKey SERVER_TIME = IrcTagKey{"", "time", false};
}  // namespace IrcTags
