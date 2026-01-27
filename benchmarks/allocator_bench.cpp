#include <benchmark/benchmark.h>
#include "memory_allocator.hpp"
#include <cstdlib> // For standard library malloc

// Measure latency of the custom allocator implementation
static void BM_MyMalloc(benchmark::State& state) {
    for (auto _ : state) {
        void* p = mem_alloc::my_malloc(128);
        
        // Prevent compiler from optimizing away the unused pointer (dead code elimination)
        benchmark::DoNotOptimize(p); 
        
        mem_alloc::free(p);
    }
}
BENCHMARK(BM_MyMalloc);

// Performance baseline using the standard system malloc
static void BM_SystemMalloc(benchmark::State& state) {
    for (auto _ : state) {
        void* p = std::malloc(128);
        
        benchmark::DoNotOptimize(p);
        std::free(p);
    }
}
BENCHMARK(BM_SystemMalloc);

// Framework entry point - generates the main() function
BENCHMARK_MAIN();