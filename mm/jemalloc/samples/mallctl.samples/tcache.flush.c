#include <stdio.h>
#include <jemalloc/jemalloc.h>
#include "swapper.h"

//tcache.flush (unsigned) -w
//	Flush the specified thread-specific cache (tcache). The same considerations apply to this interface as to thread.
//	tcache.flush, except that the tcache will never be automatically discarded.
//	flush线程特有的cache，

void get_jemalloc_tcache_create(unsigned *value)
{
	size_t size = sizeof(unsigned);
	je_mallctl("tcache.create", value, &size, NULL, 0);
}
void jemalloc_tcache_flush()
{
	je_mallctl("tcache.flush", NULL, NULL, NULL, 0);
}



int main(int argc,char **argv)
{
	unsigned value = 1;

	get_jemalloc_tcache_create(&value);
	printf("value = %d\n", value);

	char *str = je_malloc(1025);

	get_jemalloc_tcache_create(&value);
	printf("value = %d\n", value);

	je_free(str);

	get_jemalloc_tcache_create(&value);
	printf("value = %d\n", value);

	jemalloc_tcache_flush();
	je_free(str);

	get_jemalloc_tcache_create(&value);
	printf("value = %d\n", value);

	jemalloc_tcache_flush();

	get_jemalloc_tcache_create(&value);
	printf("value = %d\n", value);

}




