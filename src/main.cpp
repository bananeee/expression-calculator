#include "calculator/parser.hpp"
#include <iostream>

int main(int argc, char* argv[]) {
    expr::ExpressionCalculator calculator;
    std::string expression = "5+5/(2+8)";
    double result = calculator.evaluate(expression);
    std::cout << "Result: " << result << std::endl;
    return 0;
}