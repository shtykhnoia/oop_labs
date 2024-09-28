#include <gtest/gtest.h>
#include "../include/check_brackets.h"



TEST(CheckBracketsTest, EmptyExpression) {
    ASSERT_TRUE(check_brackets("")) << "Failed for empty expression";
}


TEST(CheckBracketsTest, CorrectBrackets) {
    ASSERT_TRUE(check_brackets("()")) << "Failed for correct brackets";
    ASSERT_TRUE(check_brackets("(())")) << "Failed for correct nested brackets";
    ASSERT_TRUE(check_brackets("((()))")) << "Failed for correct multiple nested brackets";
}

TEST(CheckBracketsTest, BracketsWithSpaces) {
    ASSERT_TRUE(check_brackets(" ( ) ")) << "Failed for correct brackets with spaces";
}

TEST(CheckBracketsTest, IncorrectBrackets) {
    ASSERT_FALSE(check_brackets(")(")) << "Failed for incorrect brackets";
    ASSERT_FALSE(check_brackets("((")) << "Failed for incorrect brackets";
    ASSERT_FALSE(check_brackets("))")) << "Failed for incorrect brackets";
    ASSERT_FALSE(check_brackets("(())(")) << "Failed for incorrect nested brackets";
    ASSERT_FALSE(check_brackets("((())")) << "Failed for incorrect multiple nested brackets";
}

TEST(CheckBracketsTest, SpecialCharacters) {
    ASSERT_FALSE(check_brackets("x()")) << "Failed for expression with special characters inside brackets";
    ASSERT_FALSE(check_brackets("(123)")) << "Failed for expression with special characters inside brackets";
    ASSERT_FALSE(check_brackets("(]))")) << "Failed for expression with special characters inside brackets";
}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}