# SPDX-FileCopyrightText: 2005-2025 Quassel Project <devel@quassel-irc.org>
# SPDX-License-Identifier: GPL-2.0-or-later

quassel_add_module(Test::Util EXPORT NOINSTALL)

target_sources(${TARGET} PRIVATE
    invocationspy.cpp
    mockedpeer.cpp
)

target_link_libraries(${TARGET}
    PUBLIC
        Boost::boost
        Quassel::Common
        Quassel::Test::Global
)
