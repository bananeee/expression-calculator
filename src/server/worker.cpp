#include "server/worker.hpp"

namespace expr {

void Worker::start() { read(); }

void Worker::read() {
    auto self(shared_from_this());
    asio::async_read_until(
        socket_, buffer_, DELIMITER,
        [this, self](std::error_code ec, std::size_t length) {
            if (!ec) {
                std::istream is(&buffer_);
                std::string expression;
                std::getline(is, expression);

                try {
                    double result = parser_.evaluate(expression);
                    write(std::to_string(result) + "\n");
                } catch (const ParseError& e) {
                    write("Error: " + std::string(e.what()) + "\n");
                }
            }
        });
}

void Worker::write(const std::string& response) {
    auto self(shared_from_this());
    asio::async_write(socket_, asio::buffer(response),
                      [this, self](std::error_code ec, std::size_t /*length*/) {
                          if (!ec) {
                              read();
                          }
                      });
}

}  // namespace expr