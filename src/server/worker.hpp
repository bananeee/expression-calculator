#pragma once

#include <asio.hpp>
#include <memory>
#include <string>

#include "calculator/parser.hpp"

namespace expr {
class Worker : public std::enable_shared_from_this<Worker> {
public:
    explicit Worker(asio::ip::tcp::socket socket)
        : socket_(std::move(socket)) {}

    void start();

private:
    void read();
    void write(const std::string& response);

    asio::ip::tcp::socket socket_;
    asio::streambuf buffer_;
    ExpressionCalculator parser_;
    static constexpr char DELIMITER = '\n';
};
}  // namespace expr
