#ifndef MEMORY_MAP_H
#define MEMORY_MAP_H

#include <sys/mman.h>
#include <stddef.h>

void* create_shared_memory(size_t size);

void release_shared_memory(void *shared_mem, size_t size);

#endif 
