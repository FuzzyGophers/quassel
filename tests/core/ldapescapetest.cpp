// SPDX-FileCopyrightText: 2005-2025 Quassel Project <devel@quassel-irc.org>
// SPDX-License-Identifier: GPL-2.0-or-later

#include "testglobal.h"

#include "ldapescaper.h"

TEST(LdapEscapeTest, unescaped)
{
    EXPECT_EQ("Babs Jensen",
              LdapEscaper::escapeQuery("Babs Jensen"));
    EXPECT_EQ("Tim Howes",
              LdapEscaper::escapeQuery("Tim Howes"));
    EXPECT_EQ("Babs J\\2a",
              LdapEscaper::escapeQuery("Babs J*"));
}

TEST(LdapEscapeTest, escaped)
{
    EXPECT_EQ("Parens R Us \\28for all your parenthetical needs\\29",
              LdapEscaper::escapeQuery("Parens R Us (for all your parenthetical needs)"));
    EXPECT_EQ("\\2a",
              LdapEscaper::escapeQuery("*"));
    EXPECT_EQ("C:\\5cMyFile",
              LdapEscaper::escapeQuery("C:\\MyFile"));
    EXPECT_EQ("Lu\\c4\\8di\\c4\\87",
              LdapEscaper::escapeQuery("Lu\xc4\x8di\xc4\x87"));
    EXPECT_EQ("\u0004\u0002Hi",
              LdapEscaper::escapeQuery("\x04\x02\x48\x69"));
}
