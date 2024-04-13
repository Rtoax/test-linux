#include <gperftools/tcmalloc.h>
#include <stdio.h>

int main(void)
{
	char *str = tc_malloc(1024);

	tc_free_sized(str, 512);

	printf("%ld\n", tc_malloc_size(str));

	*(str + 524) = 'A';

	tc_free(str);
}

