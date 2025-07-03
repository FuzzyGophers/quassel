// SPDX-FileCopyrightText: 2005-2025 Quassel Project <devel@quassel-irc.org>
// SPDX-License-Identifier: GPL-2.0-or-later

#include "test-main-export.h"

#include <QCoreApplication>

#include <gmock/gmock.h>

TEST_MAIN_EXPORT int main(int argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    QCoreApplication app(argc, argv);

    return RUN_ALL_TESTS();
}
