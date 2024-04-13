#include <gperftools/tcmalloc.h>
#include <stdio.h>

int main(void)
{
	char *str = tc_malloc_skip_new_handler(1024);
	printf("%s\n", str);
	tc_free(str);
}

