cmake_minimum_required(VERSION 3.27)

# Project name
project(MemoryAllocator)

# Set the C++ standard
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Download GTest on the fly
include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/refs/heads/main.zip
)
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE) # Avoid MSVC runtime conflicts
FetchContent_MakeAvailable(googletest)

# Core library
add_library(allocator_lib src/memory_allocator.cpp)
target_include_directories(allocator_lib PUBLIC include)

# Unit tests
add_executable(allocator_tests tests/allocator_test.cpp)
target_link_libraries(allocator_tests GTest::gtest_main allocator_lib)

# Setup Google Benchmark
FetchContent_Declare(
  benchmark
  URL https://github.com/google/benchmark/archive/refs/heads/main.zip
)
FetchContent_MakeAvailable(benchmark)

# Unit tests
add_executable(allocator_bench benchmarks/allocator_bench.cpp)
target_link_libraries(allocator_bench benchmark::benchmark allocator_lib)