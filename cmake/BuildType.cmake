# SPDX-FileCopyrightText: 2018-2025 Quassel Project <devel@quassel-irc.org>
# SPDX-License-Identifier: GPL-2.0-or-later

# Derived from Marcus D. Hanwell's suggestion
# https://blog.kitware.com/cmake-and-the-default-build-type/

# Set a default build type if none was specified
set(default_build_type "Release")

# For builds from Git, default to Debug
if (EXISTS "${CMAKE_SOURCE_DIR}/.git")
    set(default_build_type "Debug")
endif()

# Multi-config generators (such as the VS one) will set the config types
if (NOT CMAKE_BUILD_TYPE AND NOT CMAKE_CONFIGURATION_TYPES)
    message(STATUS "Setting build type to '${default_build_type}' as none was specified.")
    set(CMAKE_BUILD_TYPE "${default_build_type}" CACHE
        STRING "Choose the type of build." FORCE)
    # Set the possible values of build type for cmake-gui
    set_property(CACHE CMAKE_BUILD_TYPE PROPERTY STRINGS "Debug" "Release" "MinSizeRel" "RelWithDebInfo")
else()
    message(STATUS "CMake build type: ${CMAKE_BUILD_TYPE}")
endif()
