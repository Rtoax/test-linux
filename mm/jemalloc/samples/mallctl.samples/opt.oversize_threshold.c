#include <stdio.h>
#include <jemalloc/jemalloc.h>
#include "swapper.h"

//opt.oversize_threshold (size_t) r-
//	The threshold in bytes of which requests are considered oversize. Allocation requests with greater sizes are
//	fulfilled from a dedicated arena (automatically managed, however not within narenas), in order to reduce
//	fragmentation by not mixing huge allocations with small ones. In addition, the decay API guarantees on the extents
//	greater than the specified threshold may be overridden. Note that requests with arena index specified via
//	MALLOCX_ARENA, or threads associated with explicit arenas will not be considered. The default threshold is 8MiB.
//	Values not within large size classes disables this feature.
//	门限字节数，考虑到太大。为了解决不在小空间里申请大内存。默认大小是 8M ，MALLOCX_ARENA

void get_jemalloc_opt_oversize_threshold(size_t *value) {
	size_t size = 4;
	je_mallctl("opt.oversize_threshold", value, &size, NULL, 0);
}


int main(int argc,char **argv)
{
	size_t value = 0;

	get_jemalloc_opt_oversize_threshold(&value);
	printf("value = %ld, %ld, %ld MiB\n", value, value/1024, value/1024/1024);
}


