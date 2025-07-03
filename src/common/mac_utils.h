// SPDX-FileCopyrightText: 2005-2025 Quassel Project <devel@quassel-irc.org>
// SPDX-License-Identifier: GPL-2.0-or-later

#ifndef MAC_UTILS_H
#define MAC_UTILS_H

#include <QString>

#include <CoreFoundation/CoreFoundation.h>

QString CFStringToQString(CFStringRef str);

#endif  // MAC_UTILS_H
