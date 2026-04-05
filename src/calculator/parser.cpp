#include "calculator/parser.hpp"

namespace expr {

double ExpressionCalculator::evaluate(std::string_view expression) {
    std::stack<char> operator_stack;
    std::stack<double> operand_stack;

    Tokenizer tokenizer(expression);

    while (true) {
        Token token = tokenizer.nextToken();
        if (token.type == TokenType::End) {
            break;
        }

        switch (token.type) {
            case TokenType::Number:
                operand_stack.push(token.value);
                break;

            case TokenType::Operator:
                while (!operator_stack.empty() &&
                       precedence_[operator_stack.top()] >= precedence_[token.op]) {
                    apply_operator(operator_stack, operand_stack);
                }
                operator_stack.push(token.op);
                break;

            case TokenType::LeftParen:
                operator_stack.push(token.op);
                break;

            case TokenType::RightParen:
                while (!operator_stack.empty() && operator_stack.top() != '(') {
                    apply_operator(operator_stack, operand_stack);
                }
                if (!operator_stack.empty()) {
                    operator_stack.pop();
                }
                break;

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
