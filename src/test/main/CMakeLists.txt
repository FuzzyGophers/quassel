# SPDX-FileCopyrightText: 2005-2025 Quassel Project <devel@quassel-irc.org>
# SPDX-License-Identifier: GPL-2.0-or-later

quassel_add_module(Test::Main EXPORT NOINSTALL)

target_sources(${TARGET} PRIVATE
    main.cpp
)

target_link_libraries(${TARGET}
    PUBLIC
        ${QT_FULL}::Core
        Quassel::Test::Global
)
