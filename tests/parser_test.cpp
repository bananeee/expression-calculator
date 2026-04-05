#include <gtest/gtest.h>
#include "calculator/parser.hpp"

using namespace expr;

TEST(ParserTest, SimpleAddition) {
    ExpressionCalculator calc;
    EXPECT_EQ(calc.evaluate("1+2"), 3.0);
}

TEST(ParserTest, OperatorPrecedence) {
    ExpressionCalculator calc;
    EXPECT_EQ(calc.evaluate("2+3*4"), 14.0);
}

TEST(ParserTest, ParenthesesOverridePrecedence) {
    ExpressionCalculator calc;
    EXPECT_EQ(calc.evaluate("(2+3)*4"), 20.0);
}

TEST(ParserTest, NestedParentheses) {
    ExpressionCalculator calc;
    EXPECT_EQ(calc.evaluate("((2+3))*4"), 20.0);
}

TEST(ParserTest, SubtractionAndDivision) {
    ExpressionCalculator calc;
    EXPECT_EQ(calc.evaluate("10-3"), 7.0);
    EXPECT_EQ(calc.evaluate("9/3"), 3.0);
}

TEST(ParserTest, ThrowsOnEmptyExpression) {
    ExpressionCalculator calc;
    EXPECT_THROW(calc.evaluate(""), ParseError);
}

TEST(ParserTest, ThrowsOnTrailingOperator) {
    ExpressionCalculator calc;
    EXPECT_THROW(calc.evaluate("1+"), ParseError);
}

TEST(ParserTest, ThrowsOnMismatchedOpenParen) {
    ExpressionCalculator calc;
    EXPECT_THROW(calc.evaluate("(1+2"), ParseError);
}

TEST(ParserTest, ThrowsOnUnmatchedCloseParen) {
    ExpressionCalculator calc;
    EXPECT_THROW(calc.evaluate("1+2)"), ParseError);
}
