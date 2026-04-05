#pragma once

#include <stdexcept>
#include <string_view>

namespace expr {

class ParseError : public std::runtime_error {
public:
    using std::runtime_error::runtime_error;
};

enum class TokenType {
    Number,
    Operator,
    LeftParen,
    RightParen,
    End
};

struct Token {
    TokenType type;
    double value = 0;
    char op = '\0';
};

class Tokenizer {
public:
    explicit Tokenizer(std::string_view expression) : expression_(expression), pos_(0) {}

    Token nextToken();

private:
    std::string_view expression_;
    size_t pos_ = 0;
};

} // namespace expr
