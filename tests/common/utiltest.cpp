// SPDX-FileCopyrightText: 2005-2025 Quassel Project <devel@quassel-irc.org>
// SPDX-License-Identifier: GPL-2.0-or-later

#include "util.h"

#include <QDateTime>
#include <QDebug>
#include <QTimeZone>

#include "testglobal.h"

TEST(UtilTest, formatDateTimeToOffsetISO)
{
    QDateTime dateTime{{2006, 01, 02}, {15, 04, 05}, QTimeZone{"UTC+01:00"}};

    ASSERT_TRUE(dateTime.isValid());
    ASSERT_FALSE(dateTime.isNull());

    EXPECT_EQ(formatDateTimeToOffsetISO(dateTime), QString("2006-01-02 15:04:05+01:00"));
    EXPECT_EQ(formatDateTimeToOffsetISO(dateTime.toUTC()), QString("2006-01-02 14:04:05Z"));
    EXPECT_EQ(formatDateTimeToOffsetISO(dateTime.toOffsetFromUtc(0)), QString("2006-01-02 14:04:05Z"));
    EXPECT_EQ(formatDateTimeToOffsetISO(dateTime.toOffsetFromUtc(7200)), QString("2006-01-02 16:04:05+02:00"));
    EXPECT_EQ(formatDateTimeToOffsetISO(dateTime.toTimeZone(QTimeZone{"UTC"})), QString("2006-01-02 14:04:05Z"));
}
