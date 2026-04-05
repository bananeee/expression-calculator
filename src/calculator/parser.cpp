#include "calculator/parser.hpp"

namespace expr
{

bool ExpressionCalculator::is_operator(char c) {
    return this->precedence_.count(c);
}

bool ExpressionCalculator::is_digit(char c) {
    return c >= '0' && c <= '9';
}

double ExpressionCalculator::evaluate(const std::string& expression) {
    std::stack<char> operator_stack;
    std::stack<double> operand_stack;


    for (const char& token: expression) {
        if (is_digit(token)) {
            operand_stack.push(token - '0');
        } else if (is_operator(token)) {
            while (!operator_stack.empty() && precedence_[operator_stack.top()] >= precedence_[token]) {
                apply_operator(operator_stack, operand_stack);
            }

            operator_stack.push(token);
        } else if (token == '(') {
            operator_stack.push(token);
        } else if (token == ')') {
            while (!operator_stack.empty() && operator_stack.top() != '(') {
                apply_operator(operator_stack, operand_stack);
            }
            if (!operator_stack.empty()) {
                operator_stack.pop(); // Pop the '('
            }
        }
    }

    while (!operator_stack.empty()) {
        apply_operator(operator_stack, operand_stack);
    }
    
    return operand_stack.top();
}

void ExpressionCalculator::apply_operator(std::stack<char>& operator_stack, std::stack<double>& operand_stack) {
    char op = operator_stack.top();
    operator_stack.pop();

    double right = operand_stack.top();
    operand_stack.pop();
    double left = operand_stack.top();
    operand_stack.pop();

    double result;
    switch (op) {
        case '+': result = left + right; break;
        case '-': result = left - right; break;
        case '*': result = left * right; break;
        case '/': result = left / right; break;
    }
    operand_stack.push(result);
}


} // namespace expr
