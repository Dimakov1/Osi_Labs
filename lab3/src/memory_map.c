#include <sys/mman.h>
#include <stddef.h>
#include "memory_map.h"
#include "error_handling.h"

void* create_shared_memory(size_t size) {
    void *shared_mem = mmap(NULL, size, PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, -1, 0);
    if (shared_mem == MAP_FAILED) {
        handle_error("mmap failed");
    }
    return shared_mem;
}

void release_shared_memory(void *shared_mem, size_t size) {
    if (munmap(shared_mem, size) == -1) {
        handle_error("munmap failed");
    }
}
