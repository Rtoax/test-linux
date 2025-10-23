// SPDX-License-Identifier: (LGPL-2.1 OR BSD-2-Clause)
#include <string.h>
#include <sys/types.h>
#include <sys/file.h>
#include <dirent.h>
#include <fcntl.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <fnmatch.h>
#include <inttypes.h>
#include <stdarg.h>
#include <unistd.h>
#include <errno.h>
#include <sys/mman.h>
#include <sys/queue.h>
#include <sys/stat.h>
#include <sys/syscall.h>
#include <linux/mman.h> /* for hugetlb-related flags */

#include "mmap_helpers.h"


void *sys_mmap(void *addr, size_t length, int prot, int flags, int fd,
	       off_t offset)
{
	return (void *)syscall(__NR_mmap, addr, length, prot, flags, fd, offset);
}

void *sys_munmap(void *addr, size_t length)
{
	return (void *)syscall(__NR_munmap, addr);
}

/*
 * Uses mmap to create a shared memory area for storage of data
 * Used in this file to store the hugepage file map on disk
 */
void *map_shared_memory(const char *filename, const size_t mem_size, int flags)
{
	void *retval;
	int fd = open(filename, flags, 0600);
	if (fd < 0)
		return NULL;
	if (ftruncate(fd, mem_size) < 0) {
		close(fd);
		return NULL;
	}
	retval = mmap(NULL, mem_size, PROT_READ | PROT_WRITE, MAP_SHARED, fd,
		      0);
	close(fd);
	return retval;
}

void *open_shared_memory(const char *filename, const size_t mem_size)
{
	return map_shared_memory(filename, mem_size, O_RDWR);
}

void *create_shared_memory(const char *filename, const size_t mem_size)
{
	return map_shared_memory(filename, mem_size, O_RDWR | O_CREAT);
}

