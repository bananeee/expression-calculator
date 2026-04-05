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
./build/expression_calculator 0.0.0.0 8080 4
```

Arguments: bind address, port, number of threads. Use thread count equal to your CPU cores.

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
./build/generator --count 100 --depth 4 | nc localhost 8080
```

Options:
- `--count N` — number of expressions (default 1)
- `--depth D` — how nested the expressions get (default 4)
- `--seed S` — fixed seed for reproducible output

## Supported operations

`+` `-` `*` `/` and parentheses, with standard precedence. Integer inputs only. Division may produce a decimal result.