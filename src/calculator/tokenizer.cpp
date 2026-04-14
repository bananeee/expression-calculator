#include "calculator/tokenizer.hpp"

#include <cctype>
#include <string>

namespace expr {

Token Tokenizer::nextToken() {
    while (pos_ < expression_.size() && isspace(expression_[pos_])) {
        pos_++;
    }

    if (pos_ >= expression_.size()) {
        return {TokenType::End};
    }

    char current = expression_[pos_];

    if (isdigit(current)) {
        long long value = 0;
        while (pos_ < expression_.size() && isdigit(expression_[pos_])) {
            value = value * 10 + (expression_[pos_] - '0');
            pos_++;
        }
        return {TokenType::Number, value};
    }

    if (current == '+' || current == '-' || current == '*' || current == '/') {
        pos_++;
        return {TokenType::Operator, 0, current};
    }

    if (current == '(') {
        pos_++;
        return {TokenType::LeftParen, 0, current};
    }

    if (current == ')') {
        pos_++;
        return {TokenType::RightParen, 0, current};
    }

    throw ParseError("Invalid character: " + std::string(1, current));
}

}  // namespace expr
