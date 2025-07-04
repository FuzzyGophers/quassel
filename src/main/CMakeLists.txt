# SPDX-FileCopyrightText: 2005-2025 Quassel Project <devel@quassel-irc.org>
# SPDX-License-Identifier: GPL-2.0-or-later

if (HAVE_UMASK)
    set_property(SOURCE main.cpp APPEND PROPERTY COMPILE_DEFINITIONS HAVE_UMASK)
endif()

if (WITH_BUNDLED_ICONS)
    set_property(SOURCE main.cpp APPEND PROPERTY COMPILE_DEFINITIONS WITH_BUNDLED_ICONS)
endif()

# Windows icon resource
if(WIN32)
    if(MINGW)
        find_program(WINDRES_EXECUTABLE NAMES windres)
        if(WINDRES_EXECUTABLE)
            exec_program(windres
                ARGS "-i ${CMAKE_SOURCE_DIR}/pics/win32.rc"
                     "-o ${CMAKE_CURRENT_BINARY_DIR}/win32.o"
                     "--include-dir=${CMAKE_SOURCE_DIR}/pics"
                )
            set(WIN_RC ${CMAKE_CURRENT_BINARY_DIR}/win32.o)
        endif()
    else()
        set(WIN_RC ${CMAKE_SOURCE_DIR}/pics/win32.rc)
    endif()
endif()

# Build the executables
if (WANT_CORE)
    quassel_add_executable(quasselcore COMPONENT Core SOURCES main.cpp ${WIN_RC} LIBRARIES ${QT_FULL}::Core Quassel::Core)
endif()

if (WANT_QTCLIENT)
    set(libs ${QT_FULL}::Core ${QT_FULL}::Gui Quassel::QtUi)
    if (WITH_KDE)
        list(APPEND libs ${KF_FULL}::CoreAddons)
    endif()
    quassel_add_executable(quasselclient COMPONENT Client SOURCES main.cpp ${WIN_RC} LIBRARIES ${libs})
endif()

if (WANT_MONO)
    set(libs ${QT_FULL}::Core ${QT_FULL}::Gui Quassel::Core Quassel::QtUi)
    if (WITH_KDE)
        list(APPEND libs ${KF_FULL}::CoreAddons)
    endif()
    quassel_add_executable(quassel COMPONENT Mono SOURCES main.cpp monoapplication.cpp ${WIN_RC} LIBRARIES ${libs})
endif()
