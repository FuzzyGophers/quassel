# SPDX-FileCopyrightText: 2005-2025 Quassel Project <devel@quassel-irc.org>
# SPDX-License-Identifier: GPL-2.0-or-later

quassel_add_module(Test::Global EXPORT NOINSTALL)

target_sources(${TARGET} PRIVATE
    printers.cpp
    testglobal.h
)

target_link_libraries(${TARGET}
    PUBLIC
        GTest::GTest
        ${QT_FULL}::Core
        ${QT_FULL}::Test
        Quassel::Common
)
