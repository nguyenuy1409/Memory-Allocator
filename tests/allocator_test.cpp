#include <gtest/gtest.h>
#include "memory_allocator.hpp"

// Test if malloc returns a non-null pointer
TEST(AllocatorTest, BasicAllocation) {
    void* p = mem_alloc::my_malloc(100);
    ASSERT_NE(p, nullptr);
    mem_alloc::free(p);
}

// Test memory reuse logic
TEST(AllocatorTest, ReuseBlock) {
    void* p1 = mem_alloc::my_malloc(128);
    mem_alloc::free(p1);

    // Should pick up the same block
    void* p2 = mem_alloc::my_malloc(64);
    EXPECT_EQ(p1, p2);
    
    mem_alloc::free(p2);
}