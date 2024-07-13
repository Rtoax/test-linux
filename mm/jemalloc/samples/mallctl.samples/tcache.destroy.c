#include <stdio.h>
#include <jemalloc/jemalloc.h>
#include "swapper.h"

//tcache.destroy (unsigned) -w
//	Flush the specified thread-specific cache (tcache) and make the identifier available for use during a future tcache
//	creation.

void get_jemalloc_tcache_create(unsigned *value)
{
	size_t size = sizeof(unsigned);
	je_mallctl("tcache.create", value, &size, NULL, 0);
}
void jemalloc_tcache_destroy(unsigned value)
{
	size_t size = sizeof(unsigned);
	je_mallctl("tcache.destroy", NULL, 0, &value, size);
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

	jemalloc_tcache_destroy(value);
	jemalloc_tcache_destroy(value-1);


	get_jemalloc_tcache_create(&value);
	printf("value = %d\n", value);

}





