#include <gtest/gtest.h>
#include "../include/eleven.h"

TEST(ElevenTest, CompareEqual) {
    Eleven e1("2A");
    Eleven e2("2A");
    ASSERT_TRUE(e1.equal(e2));
    ASSERT_FALSE(e1.not_equal(e2));
    ASSERT_FALSE(e1.lower_than(e2));
    ASSERT_FALSE(e1.greater_than(e2));
}

TEST(ElevenTest, CompareGreater) {
    Eleven e1("2A");
    Eleven e2("19");
    ASSERT_TRUE(e1.greater_than(e2));
    ASSERT_FALSE(e1.lower_than(e2));
}

TEST(ElevenTest, CompareLower) {
    Eleven e1("19");
    Eleven e2("2A");
    ASSERT_TRUE(e1.lower_than(e2));
    ASSERT_FALSE(e1.greater_than(e2));
}

TEST(ElevenTest, ConstructorWithInitializerList) {
    Eleven e({'A', '3', '7'});
    ASSERT_TRUE(e.equal(Eleven("73A"))); // Проверяем с помощью метода equal
}

TEST(ElevenTest, ConstructorWithString) {
    Eleven e("A37");
    ASSERT_TRUE(e.equal(Eleven("A37"))); // Проверяем с помощью метода equal
}

TEST(ElevenTest, PlusOperation) {
    Eleven e1("A0");
    Eleven e2("2A");
    Eleven result = e1.plus(e2);
    ASSERT_TRUE(result.equal(Eleven("11A"))); // Проверяем с помощью метода equal
}

TEST(ElevenTest, MinusOperation) {
    Eleven e1("2A");
    Eleven e2("A");
    Eleven result = e1.minus(e2);
    ASSERT_TRUE(result.equal(Eleven("20"))); // Проверяем с помощью метода equal
}

TEST(ElevenTest, PlusWithCarry) {
    Eleven e1("A5");
    Eleven e2("A6");
    Eleven result = e1.plus(e2);
    ASSERT_TRUE(result.equal(Eleven("1A0"))); // Проверяем с помощью метода equal
}

TEST(ElevenTest, MinusWithBorrow) {
    Eleven e1("100");
    Eleven e2("1");
    Eleven result = e1.minus(e2);
    ASSERT_TRUE(result.equal(Eleven("AA")));
}

TEST(ElevenTest, EdgeCaseZeroMinusZero) {
    Eleven e1("0");
    Eleven e2("0");
    Eleven result = e1.minus(e2);
    ASSERT_TRUE(result.equal(Eleven("0"))); // Проверяем с помощью метода equal
}

TEST(ElevenTest, EdgeCaseLargeNumberAddition) {
    Eleven e1("A0000000A");
    Eleven e2("A0000000A");
    Eleven result = e1.plus(e2);
    ASSERT_TRUE(result.equal(Eleven("1900000019"))); // Проверяем с помощью метода equal
}

int main(int argc, char **argv)
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
