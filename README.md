# Memory Allocator

A simple C++ project to understand how memory management works at a low level. I built this allocator using the First-fit strategy and mmap system calls.

## How it works
* Strategy: It uses a Linked List to keep track of free and allocated memory blocks (First-fit).
* System Call: I used mmap to request memory directly from the OS.
* Thread-Safety: Included a std::mutex to make sure it works in multi-threaded environments.
* Alignment: Memory is 16-byte aligned for better performance and hardware compatibility.

## My Results
I used Google Benchmark to compare my allocator with the standard malloc on my machine (WSL Ubuntu).

| Benchmark | Time | Iterations |
| :--- | :--- | :--- |
| My Allocator | 15.3 ns | 42,157,285 |
| System Malloc | 11.1 ns | 62,659,446 |

*Even though it's a simple project, the speed is quite close to the system's malloc!*

## How to Build and Run

### 1. Build the project
```bash
mkdir -p build && cd build
cmake -DCMAKE_BUILD_TYPE=Release ..
make
```
### 2. Run Tests
```bash
./allocator_tests
```
### 3. Run Benchmarks
```bash
./allocator_bench
```
