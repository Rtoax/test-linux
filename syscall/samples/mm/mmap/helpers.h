#pragma once
#include <sys/types.h>
void* map_shared_memory(const char *filename, const size_t mem_size, int flags);
void* open_shared_memory(const char *filename, const size_t mem_size);
void* create_shared_memory(const char *filename, const size_t mem_size);
