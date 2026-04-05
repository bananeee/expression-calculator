cmake_minimum_required(VERSION 3.16)
project(expression-calculator VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

include(FetchContent)

FetchContent_Declare(
    asio
    GIT_REPOSITORY https://github.com/chriskohlhoff/asio.git
    GIT_TAG asio-1-28-0
)
FetchContent_MakeAvailable(asio)

add_library(asio INTERFACE)
target_include_directories(asio INTERFACE ${asio_SOURCE_DIR}/asio/include)
target_compile_definitions(asio INTERFACE ASIO_STANDALONE)
find_package(Threads REQUIRED)
target_link_libraries(asio INTERFACE Threads::Threads)

add_library(calculator_lib STATIC
    src/calculator/parser.cpp
    src/calculator/tokenizer.cpp
)
target_include_directories(calculator_lib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/src)

add_library(server_lib STATIC
    src/server/worker.cpp
    src/server/server.cpp
)
target_include_directories(server_lib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/src)
target_link_libraries(server_lib PUBLIC asio calculator_lib)

add_executable(expression_calculator src/main.cpp)
target_link_libraries(expression_calculator PRIVATE server_lib)

FetchContent_Declare(
    googletest
    GIT_REPOSITORY https://github.com/google/googletest.git
    GIT_TAG v1.14.0
)
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

enable_testing()

add_executable(calculator_tests
    tests/tokenizer_test.cpp
    tests/parser_test.cpp
)
target_link_libraries(calculator_tests PRIVATE calculator_lib GTest::gtest_main)
include(GoogleTest)
gtest_discover_tests(calculator_tests)

add_executable(generator src/generator/main.cpp)