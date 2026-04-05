#include <iostream>

#include "calculator/parser.hpp"

int main(int argc, char* argv[]) {
    expr::ExpressionCalculator calculator;
    std::string expression = "15 +    5/ (22+  8 ) ";

    try {
        double result = calculator.evaluate(expression);
        std::cout << "Result: " << result << std::endl;
    } catch (const expr::ParseError& e) {
        // parsing error
    }
    return 0;
}
