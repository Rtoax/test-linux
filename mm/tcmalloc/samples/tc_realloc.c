#include <gperftools/tcmalloc.h>
#include <stdio.h>

int main(void)
{
	char *str = tc_malloc(1024);
	printf("%ld\n", tc_malloc_size(str));
	str = tc_realloc(str, 2024);
	printf("%ld\n", tc_malloc_size(str));
	tc_free(str);
	return 0;
}


