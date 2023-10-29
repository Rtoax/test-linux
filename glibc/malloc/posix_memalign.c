#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>
#include <malloc.h>


static inline void *align_malloc(size_t align, size_t size)
{
	void *ptr;

	int ret = posix_memalign(&ptr, align, size);
	if (ret != 0) {
		fprintf(stderr, strerror(ret));
		abort();
	}

	return ptr;
}

int main(void)
{
	char *str = align_malloc(64, 1024);
	memcpy(str, "Hello", 5);
	return 0;
}
