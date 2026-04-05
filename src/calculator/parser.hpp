#pragma once
#include <map>
#include <string>
#include <stack>

namespace expr
{
    
class ExpressionCalculator {
public:
    double evaluate(const std::string& expression);

private:

    void apply_operator(std::stack<char>& operator_stack, std::stack<double>& operand_stack);

    bool is_operator(char c);    
    bool is_digit(char c);

    std::map<char, int> precedence_{
        {'+', 1}, {'-', 1},
        {'*', 2}, {'/', 2}    
    };
};
} // namespace expr
