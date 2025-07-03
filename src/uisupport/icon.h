// SPDX-FileCopyrightText: 2005-2025 Quassel Project <devel@quassel-irc.org>
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

#include "uisupport-export.h"

#include <vector>

#include <QIcon>
#include <QString>

namespace icon {

/**
 * Gets an icon from the current icon theme.
 *
 * If the theme does not provide the icon, tries to load the icon from the
 * fallback path, if given.
 *
 * If no icon can be found, a warning is displayed and a null icon returned.
 *
 * @param iconName     Icon name
 * @param fallbackPath Full path to a fallback icon
 * @returns The requested icon, if available
 */
UISUPPORT_EXPORT QIcon get(const QString& iconName, const QString& fallbackPath = {});

/**
 * Gets an icon from the current icon theme.
 *
 * If the theme does not provide any of the given icon names, tries to load the
 * icon from the fallback path, if given.
 *
 * If no icon can be found, a warning is displayed and a null icon returned.
 *
 * @param iconNames    List of icon names (first match wins)
 * @param fallbackPath Full path to a fallback icon
 * @returns The requested icon, if available
 */
UISUPPORT_EXPORT QIcon get(const std::vector<QString>& iconNames, const QString& fallbackPath = {});

}  // namespace icon
