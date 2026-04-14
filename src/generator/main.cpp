#include <cstdlib>
#include <iostream>
#include <random>
#include <string>

std::random_device rd;
std::default_random_engine engine(rd());

const int MAX_RAND_VALUE = 99;
const int MIN_RAND_VALUE = 1;
const char ops[] = {'+', '-', '*', '/'};

/**
 * @brief Generate random arithmetic expressions.
 * @param depth The maximum depth of nested expressions.
 * @return A random arithmetic expression as a string.
 */
std::string generate(int depth) {
    std::uniform_int_distribution<int> coin(0, 1);
    if (depth == 0 || coin(engine) == 0) {
        std::uniform_int_distribution<int> num(MIN_RAND_VALUE, MAX_RAND_VALUE);
        return std::to_string(num(engine));
    }

    std::uniform_int_distribution<int> op_dist(0, 3);
    char op = ops[op_dist(engine)];

    std::string left = generate(depth - 1);
    std::string right = generate(depth - 1);

    return "(" + left + op + right + ")";
}

/**
 * @brief Generate random arithmetic expressions.
 * @param size The approximate size of the generated expression in characters
 * (KB).
 * @param depth The maximum depth of nested expressions.
 * @return A random arithmetic expression as a string.
 */
std::string generate(size_t size, int depth) {
    std::string expr;
    std::uniform_int_distribution<int> num(0, depth);
    std::uniform_real_distribution<double> real(0.0, 1.0);
    const double base_dup_prob = 0.5;

    while (expr.size() < size) {
        if (expr.empty()) {
            expr = generate(num(engine));
        } else {
            double progress = static_cast<double>(expr.size()) / static_cast<double>(size);
            double dup_prob = base_dup_prob * (1.0 - progress);

            std::uniform_int_distribution<int> op_dist(0, 3);
            char op = ops[op_dist(engine)];

            // The closer the current size is, the less likely we are to duplicate the existing expression.
            if (real(engine) < dup_prob) {
                expr = expr + op + expr;
            } else {
                std::string part = generate(num(engine));
                expr = expr + op + part;
            }
        }
    }
    return expr;
}

int main(int argc, char* argv[]) {
    int count = 1;
    int depth = 4;
    unsigned seed = std::random_device{}();
    size_t size = 0;

    for (int i = 1; i < argc; ++i) {
        std::string arg(argv[i]);
        if (arg == "--count" && i + 1 < argc)
            count = std::stoi(argv[++i]);
        else if (arg == "--depth" && i + 1 < argc)
            depth = std::stoi(argv[++i]);
        else if (arg == "--seed" && i + 1 < argc)
            seed = std::stoul(argv[++i]);
        else if (arg == "--size" && i + 1 < argc)
            size = std::stoi(argv[++i]);
    }

    if (depth < 0) depth = 0;
    if (count < 0) count = 0;

    engine.seed(seed);

    for (int i = 0; i < count; ++i) {
        if (size > 0) {
            std::cout << generate(size * 1024, depth) << "\n";
        } else {
            std::cout << generate(depth) << "\n";
        }
    }

    return 0;
}
