#include "calculator/parser.hpp"

namespace expr {

long long ExpressionCalculator::evaluate(std::string_view expression) {
    std::stack<char> operator_stack;
    std::stack<long long> operand_stack;

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
                       operator_stack.top() != '(' &&
                       precedence_[operator_stack.top()] >= precedence_[token.op]) {
                    apply_operator(operator_stack, operand_stack);
                }
                operator_stack.push(token.op);
                break;

            case TokenType::LeftParen:
                operator_stack.push('(');
                break;

            case TokenType::RightParen:
                while (!operator_stack.empty() && operator_stack.top() != '(') {
                    apply_operator(operator_stack, operand_stack);
                }
                if (operator_stack.empty()) {
                    throw ParseError("Mismatched parentheses");
                }
                operator_stack.pop();
                break;

            case TokenType::End:
                break;
        }
    }

    while (!operator_stack.empty()) {
        if (operator_stack.top() == '(') {
            throw ParseError("Mismatched parentheses");
        }
        apply_operator(operator_stack, operand_stack);
    }

    if (operand_stack.empty() || operand_stack.size() != 1) {
        throw ParseError("Malformed expression");
    }

    return operand_stack.top();
}

void ExpressionCalculator::apply_operator(std::stack<char>& operator_stack,
                                          std::stack<long long>& operand_stack) {
    if (operand_stack.size() < 2) {
        throw ParseError("Malformed expression");
    }

    char op = operator_stack.top();
    operator_stack.pop();

    long long right = operand_stack.top();
    operand_stack.pop();
    long long left = operand_stack.top();
    operand_stack.pop();

    long long result;
    switch (op) {
        case '+': result = left + right; break;
        case '-': result = left - right; break;
        case '*': result = left * right; break;
        case '/':
            if (right == 0) {
                throw ParseError("Division by zero");
            }
            result = left / right;
            break;
        default:  throw ParseError("Unknown operator");
    }
    operand_stack.push(result);
}

}  // namespace expr
