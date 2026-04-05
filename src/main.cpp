#include <cstdlib>
#include <iostream>
#include <string>
#include <thread>

#include "calculator/parser.hpp"
#include "server/server.hpp"

int main(int argc, char* argv[]) {
    if (argc != 4) {
        std::cerr << "Usage: " << argv[0]
                  << " <bind_address> <port> <threads>\n";
        return 1;
    }

    std::string bind_address = argv[1];
    uint16_t port = static_cast<uint16_t>(std::stoi(argv[2]));
    size_t threads = static_cast<size_t>(std::stoi(argv[3]));

    std::cout << "Starting expression calculator server\n"
              << "  Address: " << bind_address << ":" << port << "\n"
              << "  Threads: " << threads << "\n";

    expr::Server server(bind_address, port, threads);
    server.start();

    std::cout << "Server stopped.\n";

    return 0;
}
