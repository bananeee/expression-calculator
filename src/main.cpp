#include <iostream>
#include <string>
#include <thread>

#include "calculator/parser.hpp"
#include "server/server.hpp"

void print_help(const char* program) {
    std::cout
        << "Usage: " << program << " [options]\n\n"
        << "Options:\n"
        << "  --port <port>     Port to listen on (default: "
        << expr::Server::DEFAULT_PORT << ")\n"
        << "  --bind <addr>     Address to bind to (default: "
        << expr::Server::DEFAULT_ADDRESS << ")\n"
        << "  --threads <n>     Number of worker threads (default: CPU cores)\n"
        << "  --help            Show this help message\n";
}

bool parse_args(int argc, char* argv[], uint16_t& port,
                std::string& bind_address, size_t& threads) {
    for (int i = 1; i < argc; ++i) {
        std::string arg = argv[i];

        if (arg == "--help") {
            print_help(argv[0]);
            return false;
        }

        if (arg == "--port" && i + 1 < argc) {
            port = static_cast<uint16_t>(std::stoi(argv[++i]));
        } else if (arg == "--bind" && i + 1 < argc) {
            bind_address = argv[++i];
        } else if (arg == "--threads" && i + 1 < argc) {
            threads = static_cast<size_t>(std::stoi(argv[++i]));
        }
    }

    return true;
}

int main(int argc, char* argv[]) {
    uint16_t port = expr::Server::DEFAULT_PORT;
    std::string bind_address{expr::Server::DEFAULT_ADDRESS};
    size_t threads = std::thread::hardware_concurrency();

    if (!parse_args(argc, argv, port, bind_address, threads)) {
        return 0;
    }

    std::cout << "Starting expression calculator server\n"
              << "  Address: " << bind_address << ":" << port << "\n"
              << "  Threads: " << threads << "\n";

    expr::Server server(bind_address, port, threads);
    server.start();

    std::cout << "Server stopped.\n";

    return 0;
}
