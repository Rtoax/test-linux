#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>
#include <malloc.h>
#include <unistd.h>


static inline void *align_malloc(size_t align, size_t size)
{
	void *ptr;

#if defined(ALIGNED_ALLOC)
#pragma message("Use aligned_alloc()")
	ptr = aligned_alloc(align, size);
#elif defined(VALLOC)
#pragma message("Use valloc()")
	ptr = valloc(size);
#else
#pragma message("Use posix_memalign()")
	int ret = posix_memalign(&ptr, align, size);
	if (ret != 0) {
		fprintf(stderr, "%s\n", strerror(ret));
		abort();
	}
#endif

	return ptr;
}

int main(void)
{
	size_t pgsz = getpagesize();
	char *str = align_malloc(64, pgsz);
	memcpy(str, "Hello", 5);
	free(str);
	return 0;
}
