#include <gperftools/tcmalloc.h>
#include <stdio.h>

int main(void)
{
	char *str;
	int ret = tc_posix_memalign((void**)&str, 8, 1024);
	printf("%d:%ld\n", ret, tc_malloc_size(str));

	str = tc_realloc(str, 2024);

	printf("%ld\n", tc_malloc_size(str));

	tc_free(str);
}
