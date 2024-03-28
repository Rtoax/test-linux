#include <stdio.h>
#include <gperftools/tcmalloc.h>


int main(void)
{
	char *str = tc_calloc(1024, 1);
	printf("%ld\n", tc_malloc_size(str));

	str = tc_realloc(str, 2024);

	printf("%ld\n", tc_malloc_size(str));

	tc_free(str);
	return 0;
}



