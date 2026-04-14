#include "server/worker.hpp"

namespace expr {

void Worker::start() { read(); }

void Worker::read() {
    auto self(shared_from_this());
    read_start_ = std::chrono::steady_clock::now();

    asio::async_read_until(
        socket_, buffer_, DELIMITER,
        [this, self](std::error_code ec, std::size_t length) {
            if (!ec) {
                auto now = std::chrono::steady_clock::now();
                auto duration =
                    std::chrono::duration_cast<std::chrono::milliseconds>(
                        now - read_start_)
                        .count();
                std::cout << "[timing] io_read=" << length << " bytes, in "
                          << duration << " ms\n";

                std::istream is(&buffer_);
                std::string expression;
                std::getline(is, expression);

                try {
                    auto proc_start = std::chrono::steady_clock::now();

                    long long result = calculator_.evaluate(expression);
                    std::string formatted = std::to_string(result);

                    auto proc_done = std::chrono::steady_clock::now();
                    auto proc_ms =
                        std::chrono::duration_cast<std::chrono::milliseconds>(
                            proc_done - proc_start)
                            .count();
                    std::cerr << "[timing] process=" << proc_ms << "ms\n";

                    write(formatted + "\n");
                } catch (const ParseError& e) {
                    write("Error: " + std::string(e.what()) + "\n");
                }
            }
        });
}

void Worker::write(const std::string& response) {
    auto self(shared_from_this());
    auto buf = std::make_shared<std::string>(response);
    asio::async_write(
        socket_, asio::buffer(*buf),
        [this, self, buf](std::error_code ec, std::size_t /*length*/) {
            if (!ec) {
                read();
            }
        });
}

}  // namespace expr