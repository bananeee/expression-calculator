#include <cstdlib>
#include <iostream>
#include <random>
#include <string>

static std::mt19937 rng;

std::string generate(int depth) {
    std::uniform_int_distribution<int> coin(0, 1);
    if (depth == 0 || coin(rng) == 0) {
        std::uniform_int_distribution<int> num(1, 999);
        return std::to_string(num(rng));
    }

    const char ops[] = {'+', '-', '*', '/'};
    std::uniform_int_distribution<int> op_dist(0, 3);
    char op = ops[op_dist(rng)];

    std::string left = generate(depth - 1);
    std::string right;

    if (op == '/') {
        std::uniform_int_distribution<int> divisor(1, 999);
        right = std::to_string(divisor(rng));
    } else {
        right = generate(depth - 1);
    }

    return "(" + left + op + right + ")";
}

int main(int argc, char* argv[]) {
    int count = 1;
    int depth = 4;
    unsigned seed = std::random_device{}();

    for (int i = 1; i < argc; ++i) {
        std::string arg(argv[i]);
        if (arg == "--count" && i + 1 < argc) count = std::stoi(argv[++i]);
        else if (arg == "--depth" && i + 1 < argc) depth = std::stoi(argv[++i]);
        else if (arg == "--seed" && i + 1 < argc) seed = std::stoul(argv[++i]);
    }

    if (depth < 0) depth = 0;
    if (count < 0) count = 0;

    rng.seed(seed);

    for (int i = 0; i < count; ++i) {
        std::cout << generate(depth) << "\n";
    }

    return 0;
}
