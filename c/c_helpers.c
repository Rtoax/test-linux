#include <stdio.h>
#include <malloc.h>
#include <assert.h>
#include <string.h>
#include <sys/types.h>

#include "c_helpers.h"

void *alloc_mem_internal(void **ptr, size_t size)
{
	void *p = realloc(*ptr, size);
	*ptr = p;
	return p;
}

void *alloc_mem(void **ptr, size_t size)
{
	return alloc_mem_internal(ptr, size);
}
