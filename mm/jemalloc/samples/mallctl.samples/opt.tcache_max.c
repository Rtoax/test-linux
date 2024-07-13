#include <stdio.h>
#include <jemalloc/jemalloc.h>

//opt.tcache_max (size_t) r-	The default maximum is 32 KiB (2^15)
//	Maximum size class to cache in the thread-specific cache (tcache). At a minimum, the first size class is cached; and
//	at a maximum, size classes up to 8 MiB can be cached. The default maximum is 32 KiB (2^15). As a convenience, this
//	may also be set by specifying lg_tcache_max, which will be taken to be the base-2 logarithm of the setting of
//	tcache_max

void get_jemalloc_opt_tcache_max(size_t *value) {
	size_t size = sizeof(size_t);
	je_mallctl("opt.tcache_max", value, &size, NULL, 0);
}

int main(int argc,char **argv)
{
	size_t value = true;

	get_jemalloc_opt_tcache_max(&value);
	printf("value = %d, %ld KiB\n", value, value/1024);
}



