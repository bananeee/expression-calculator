#include <cstdlib>
#include <iostream>
#include <string>
#include <thread>

#include "calculator/parser.hpp"
#include "server/server.hpp"
#include <sys/resource.h>

void raise_fd_limit() {
    struct rlimit rl;
    if (getrlimit(RLIMIT_NOFILE, &rl) == 0 && rl.rlim_cur < rl.rlim_max) {
        rl.rlim_cur = rl.rlim_max;
        setrlimit(RLIMIT_NOFILE, &rl);

        std::cout << "File descriptor limit: " << rl.rlim_cur << "\n";
    }
}

int main(int argc, char* argv[]) {
    raise_fd_limit();

    if (argc != 3) {
        std::cerr << "Usage: " << argv[0]
                  << " <port> <threads>\n";
        return 1;
    }

    std::string bind_address = "127.0.0.1";
    uint16_t port = static_cast<uint16_t>(std::stoi(argv[1]));
    size_t threads = static_cast<size_t>(std::stoi(argv[2]));

    std::cout << "Starting expression calculator server\n"
              << "  Address: " << bind_address << ":" << port << "\n"
              << "  Threads: " << threads << "\n";

    expr::Server server(bind_address, port, threads);
    server.start();

    std::cout << "Server stopped.\n";

    return 0;
}
