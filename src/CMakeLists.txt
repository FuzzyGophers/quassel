# SPDX-FileCopyrightText: 2005-2025 Quassel Project <devel@quassel-irc.org>
# SPDX-License-Identifier: GPL-2.0-or-later

add_subdirectory(common)
if (BUILD_CORE)
    add_subdirectory(core)
endif()
if (BUILD_GUI)
    add_subdirectory(client)
    add_subdirectory(uisupport)
    add_subdirectory(qtui)
endif()

if (BUILD_TESTING)
    add_subdirectory(test)
endif()

add_subdirectory(main)
