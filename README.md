# Expression Calculator

A multithreaded TCP server that evaluates math expressions. 

## Requirements

- CMake 3.16+
- A C++17 compiler (GCC or Clang)
- Internet access on first build (fetches ASIO and GoogleTest via CMake)

## Build

```bash
mkdir build && cd build
cmake ..
make -j$(nproc)
```

## Run the server

```bash
./build/expression_calculator 8080 4
```

Arguments: port, number of threads. To maximize performance, set the thread count equal to the number of your CPU cores.

## Test the server

```bash
echo "(3+2*4)*7" | nc localhost 8080
# 77

echo "10/4" | nc localhost 8080
# 2.500000
```

The connection stays open after each result, so you can keep sending expressions on the same socket.

## Run tests

```bash
cd build && ctest --output-on-failure
```

## Generate test input

The `generator` tool produces random expressions you can pipe straight to the server:

```bash
./build/generator --count 100 --depth 4 --size 100 | nc localhost 8080
```

Options:
- `--count N` - number of expressions (default 1)
- `--depth D` - how nested the expressions get (default 4)
- `--seed S` - fixed seed for reproducible output
- `--size SZ` - (optional) approximately size (in KB) of each expression 

## Supported operations
`+` `-` `*` `/` and parentheses, with standard precedence. Integer inputs only.

## Non-functional features
### Handling large expressions
Expression evaluation uses the Shunting Yard algorithm with O(n) complexity. The current design can process an approximately 1 GB expression in around 3 minutes. Since I/O accounts for only ~15% of the total time, streaming is unnecessary and would add complexity. There is still room to improve performance further, such as simplifying the tokenizer step and preallocating stack sizes.

```bash
./generator --count 1 --size 1000000 --depth 2 --seed 1000 | nc localhost 8080
# 7595711638

## Server log
Starting expression calculator server
  Address: 127.0.0.1:8080
  Threads: 4
[timing] io_read=1082823244 bytes, in 14097 ms
[timing] process=81339ms
```

### Handling 10K concurrent clients
The server uses a thread pool with asynchronous read/write via ASIO. This design allows it to handle a large number of clients without crashing.
The script `connection_test.sh` simulates 10,000 concurrent connections, each sending a 1 KB expression. While the test is simple, it demonstrates that the server can serve a large number of clients simultaneously.
Note: Linux limits the maximum number of file descriptors to 1024 by default. We must increase this limit for the server to handle more than 1024 clients at the same time.

```bash
# Run the server first

./scripts/connection_test.sh
10000/10000 requests got a response, 0 failed
```