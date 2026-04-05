#pragma once

#include <map>
#include <stack>
#include <string_view>

#include "calculator/tokenizer.hpp"

namespace expr {

class ExpressionCalculator {
   public:
    double evaluate(std::string_view expression);

   private:
    void apply_operator(std::stack<char>& operator_stack,
                        std::stack<double>& operand_stack);

    std::map<char, int> precedence_{{'+', 1}, {'-', 1}, {'*', 2}, {'/', 2}};
};
}  // namespace expr
