#pragma once

#include <cstddef> // For std::size_t

/**
 * @namespace mem_alloc
 * @brief A custom memory allocator implementation using mmap and a linked-list strategy.
 */
namespace mem_alloc {

    /**
     * @brief Allocates a block of memory of the specified size.
     * * This function searches for a previously freed block that fits the requested size.
     * If no suitable block is found, it requests new memory from the Operating System.
     * * @param requested_size Number of bytes to allocate.
     * @return void* Pointer to the allocated memory block, or nullptr if allocation fails.
     */
    void* my_malloc(std::size_t requested_size);

    /**
     * @brief Frees a previously allocated block of memory.
     * * Marks the block as free so it can be reused by future my_malloc calls.
     * Does not return memory to the OS immediately to reduce syscall overhead.
     * * @param ptr Pointer to the memory block to be freed.
     */
    void free(void* ptr);

} // namespace mem_alloc
