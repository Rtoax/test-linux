#pragma once
#include <sys/types.h>

void *sys_mmap(void *addr, size_t length, int prot, int flags, int fd,
	       off_t offset);
void *sys_munmap(void *addr, size_t length);

void *map_shared_memory(const char *filename, const size_t mem_size, int flags);
void *open_shared_memory(const char *filename, const size_t mem_size);
void *create_shared_memory(const char *filename, const size_t mem_size);
