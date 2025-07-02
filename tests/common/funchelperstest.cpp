// SPDX-License-Identifier: GPL-2.0-or-later

#include "testglobal.h"

#include <QVariantList>

#include "funchelpers.h"

TEST(FuncHelpersTest, invokeLambdaWithArgsList)
{
    int intVal{};
    QString stringVal{};

    auto callable = [&intVal, &stringVal](int i, const QString& s)
    {
        intVal = i;
        stringVal = s;
    };

    // Good case
    {
        auto ret = invokeWithArgsList(callable, {42, "Hello World"});
        ASSERT_TRUE(ret);
        EXPECT_FALSE(ret->isValid());  // Callable returns void, so the returned QVariant should be invalid
        EXPECT_EQ(42, intVal);
        EXPECT_EQ("Hello World", stringVal);
    }

    // Too many arguments
    {
        ASSERT_FALSE(invokeWithArgsList(callable, {23, "Hi Universe", 2.3}));
        // Values shouldn't have changed
        EXPECT_EQ(42, intVal);
        EXPECT_EQ("Hello World", stringVal);
    }

    // Too few arguments
    {
        ASSERT_FALSE(invokeWithArgsList(callable, {23}));
        // Values shouldn't have changed
        EXPECT_EQ(42, intVal);
        EXPECT_EQ("Hello World", stringVal);
    }

    // Cannot convert argument type
    {
        // Ensure type cannot be converted
        QVariantList wrong{"Foo", "Bar"};
        QVariant v{wrong};
        ASSERT_FALSE(v.canConvert<QString>());

        ASSERT_FALSE(invokeWithArgsList(callable, {23, wrong}));
        // Values shouldn't have changed
        EXPECT_EQ(42, intVal);
        EXPECT_EQ("Hello World", stringVal);
    }
}

TEST(FuncHelpersTest, invokeLambdaWithArgsListAndReturnValue)
{
    int intVal{};
    QString stringVal{};

    auto callable = [&intVal, &stringVal](int i, const QString& s)
    {
        intVal = i;
        stringVal = s;
        return -i;
    };

    // Good case
    {
        auto ret = invokeWithArgsList(callable, {42, "Hello World"});
        ASSERT_TRUE(ret);
        ASSERT_TRUE(ret->isValid());
        EXPECT_EQ(-42, *ret);
        EXPECT_EQ(42, intVal);
        EXPECT_EQ("Hello World", stringVal);
    }

    // Failed invocation
    {
        ASSERT_FALSE(invokeWithArgsList(callable, {23}));
    }
}

class Object
{
public:
    void voidFunc(int i, const QString& s)
    {
        intVal = i;
        stringVal = s;
    }

    int intFunc(int i)
    {
        return -i;
    }

    int intVal{};
    QString stringVal{};
};

TEST(FuncHelpersTest, invokeMemberFunction)
{
    Object object;

    // Good case
    {
        auto ret = invokeWithArgsList(&object, &Object::voidFunc, {42, "Hello World"});
        ASSERT_TRUE(ret);
        EXPECT_FALSE(ret->isValid());  // Callable returns void, so the returned QVariant should be invalid
        EXPECT_EQ(42, object.intVal);
        EXPECT_EQ("Hello World", object.stringVal);
    }

    // Good case with return value
    {
        auto ret = invokeWithArgsList(&object, &Object::intFunc, {42});
        ASSERT_TRUE(ret);
        EXPECT_EQ(-42, *ret);
    }

    // Too few arguments
    {
        auto ret = invokeWithArgsList(&object, &Object::voidFunc, {23});
        ASSERT_FALSE(ret);
        EXPECT_EQ(42, object.intVal);
    }
}
