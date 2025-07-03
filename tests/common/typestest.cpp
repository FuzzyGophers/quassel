// SPDX-FileCopyrightText: 2005-2025 Quassel Project <devel@quassel-irc.org>
// SPDX-License-Identifier: GPL-2.0-or-later

#include <cstdint>

#include <QByteArray>
#include <QDataStream>
#include <QObject>

#include "testglobal.h"
#include "types.h"

using namespace ::testing;

class EnumHolder
{
    Q_GADGET

public:
    enum class Enum16 : uint16_t {};
    enum class Enum32 : uint32_t {};

    enum class EnumQt16 : uint16_t {};
    Q_ENUM(EnumQt16)
    enum class EnumQt32 : uint32_t {};
    Q_ENUM(EnumQt32)
};

// Verify that enums are (de)serialized as their underlying type
TEST(TypesTest, enumSerialization)
{
    QByteArray data;
    QDataStream out(&data, QIODevice::WriteOnly);

    // Serialize
    out << EnumHolder::Enum16(0xabcd);
    ASSERT_THAT(data.size(), Eq(2));
    out << EnumHolder::Enum32(0x123456);
    ASSERT_THAT(data.size(), Eq(6));
    out << EnumHolder::EnumQt16(0x4321);
    ASSERT_THAT(data.size(), Eq(8));
    out << EnumHolder::Enum32(0xfedcba);
    ASSERT_THAT(data.size(), Eq(12));
    ASSERT_THAT(out.status(), Eq(QDataStream::Status::Ok));

    // Deserialize
    QDataStream in(data);
    EnumHolder::Enum16 enum16;
    EnumHolder::Enum32 enum32;
    EnumHolder::EnumQt16 enumQt16;
    EnumHolder::EnumQt32 enumQt32;
    in >> enum16  >> enum32 >> enumQt16 >> enumQt32;
    ASSERT_THAT(in.status(), Eq(QDataStream::Status::Ok));
    EXPECT_TRUE(in.atEnd());

    EXPECT_THAT((int)enum16, Eq(0xabcd));
    EXPECT_THAT((int)enum32, Eq(0x123456));
    EXPECT_THAT((int)enumQt16, Eq(0x4321));
    EXPECT_THAT((int)enumQt32, Eq(0xfedcba));
}

#include "typestest.moc"
