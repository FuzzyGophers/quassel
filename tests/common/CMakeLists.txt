# SPDX-FileCopyrightText: 2005-2025 Quassel Project <devel@quassel-irc.org>
# SPDX-License-Identifier: GPL-2.0-or-later

quassel_add_test(ExpressionMatchTest)

quassel_add_test(FuncHelpersTest)

quassel_add_test(IrcDecoderTest)

quassel_add_test(IrcEncoderTest)

quassel_add_test(SignalProxyTest
    LIBRARIES
        Quassel::Test::Util
)

quassel_add_test(TypesTest)

quassel_add_test(UtilTest)
