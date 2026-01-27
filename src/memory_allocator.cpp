#include "memory_allocator.hpp" // Header for this file
#include <iostream> // For printing status and debug messages
#include <sys/mman.h> // For mmap()
#include <mutex> // For std::mutex to make allocator thread-safe
#include <unistd.h> // Access to POSIX system API constants
#include <cstddef> // For std::size_t

namespace mem_alloc {
    struct alignas(16) Header {
        std::size_t size; // How many bytes of usable memory are in this block
        Header* next;
        bool is_free;
    };
    static Header* block_head = nullptr;
    static std::mutex alloc_mutex;

    // Request additional memory from the OS
    static Header* request_mem(std::size_t requested_size) {
        std::size_t total_size = requested_size + sizeof(Header);
        // void *mmap(void *addr, size_t length, int prot, int flags, int fd, off_t offset);
        void* block = mmap(nullptr, total_size, PROT_READ | PROT_WRITE,
                        MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);

        // Check if the system call failed
        if(block == MAP_FAILED) {
            return nullptr;
        }

        // Map raw memory to Header struct
        Header* header = reinterpret_cast<Header*>(block); // Cast void* to Header* (pointer type)
        header->size = requested_size;
        header->is_free = false;
        header->next = nullptr;

        return header;
    }

    // Search the linked list for a free block that fits the requested size
    static Header* find_free_block(std::size_t requested_size) {
        Header* curr = block_head;
        
        while(curr) {
            // Check if the block is free and has enough space
            if(curr->is_free && curr->size >= requested_size) {
                return curr;
            }
            curr = curr->next;
        }
        return nullptr;
    }

    // Allocates a block of "size" bytes
    void* my_malloc(std::size_t requested_size) {
        if(requested_size <= 0) return nullptr;

        // Lock the mutex until end of scope (Thread-safety)
        std::lock_guard<std::mutex> alloc_lock(alloc_mutex);

        // Try to find an available free block
        Header* header = find_free_block(requested_size);

        if(header) {
            header->is_free = false;
        }
        else {
            header = request_mem(requested_size);
            if(!header) return nullptr;

            header->next = block_head;
            block_head = header;
        }
        return (header + 1);
    }

    void free(void* ptr) {
        if(!ptr) return;

        // Lock the mutex until end of scope (Thread-safety)
        std::lock_guard<std::mutex> alloc_lock(alloc_mutex);

        // Backtrack to header stored at block start
        Header* header = static_cast<Header*>(ptr) - 1;

        // Mark for reuse
        header->is_free = true;
    }
}

