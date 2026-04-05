#pragma once
#include <asio.hpp>
#include <string>
#include <thread>
#include <vector>

namespace expr {
class Server {
public:
    static constexpr int DEFAULT_PORT = 9999;
    static constexpr const char* DEFAULT_ADDRESS = "0.0.0.0";

    Server(const std::string& address, int port, size_t thread_pool_size);
    ~Server();

    void start();
    void stop();

private:
    void do_accept();

    asio::io_context io_context_;
    asio::ip::tcp::acceptor acceptor_;
    asio::signal_set signals_;
    std::vector<std::thread> threads_;
    size_t thread_count_;
    std::atomic<bool> is_stopped_{true};
};
}  // namespace expr
