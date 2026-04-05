#include <gtest/gtest.h>
#include "calculator/tokenizer.hpp"

using namespace expr;

TEST(TokenizerTest, ParsesNumber) {
    Tokenizer t("42");
    Token tok = t.nextToken();
    EXPECT_EQ(tok.type, TokenType::Number);
    EXPECT_EQ(tok.value, 42.0);
}

TEST(TokenizerTest, ParsesOperators) {
    for (char op : {'+', '-', '*', '/'}) {
        Tokenizer t(std::string(1, op));
        Token tok = t.nextToken();
        EXPECT_EQ(tok.type, TokenType::Operator);
        EXPECT_EQ(tok.op, op);
    }
}

TEST(TokenizerTest, ParsesParens) {
    Tokenizer t("(");
    EXPECT_EQ(t.nextToken().type, TokenType::LeftParen);
    Tokenizer t2(")");
    EXPECT_EQ(t2.nextToken().type, TokenType::RightParen);
}

TEST(TokenizerTest, SkipsWhitespace) {
    Tokenizer t("  42  ");
    Token tok = t.nextToken();
    EXPECT_EQ(tok.type, TokenType::Number);
    EXPECT_EQ(tok.value, 42.0);
}

TEST(TokenizerTest, ThrowsOnInvalidChar) {
    Tokenizer t("@");
    EXPECT_THROW(t.nextToken(), ParseError);
}
