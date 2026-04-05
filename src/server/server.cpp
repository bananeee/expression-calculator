#include "server/server.hpp"
#include "server/worker.hpp"
#include <memory>

namespace expr {

Server::Server(const std::string& address, int port, size_t thread_pool_size)
    : acceptor_(io_context_), signals_(io_context_, SIGINT, SIGTERM),
      thread_count_(thread_pool_size) {
    asio::ip::tcp::endpoint endpoint(asio::ip::make_address(address), port);
    acceptor_.open(endpoint.protocol());
    acceptor_.set_option(asio::ip::tcp::acceptor::reuse_address(true));
    acceptor_.bind(endpoint);
    acceptor_.listen();
}

Server::~Server() { stop(); }

void Server::start() {
    is_stopped_ = false;

    signals_.async_wait([this](std::error_code, int) { stop(); });

    do_accept();
    for (size_t i = 0; i < thread_count_; ++i) {
        threads_.emplace_back([this]() { io_context_.run(); });
    }

    for (auto& thread : threads_) {
        thread.join();
    }
}

void Server::stop() {
    if (!is_stopped_) {
        is_stopped_ = true;
        io_context_.stop();
    }
}

void Server::do_accept() {
    acceptor_.async_accept(
        [this](std::error_code ec, asio::ip::tcp::socket socket) {
            if (!ec) {
                std::make_shared<Worker>(std::move(socket))->start();
            }
            if (!is_stopped_) {
                do_accept();
            }
        });
}

}  // namespace expr
