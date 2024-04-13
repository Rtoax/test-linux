#include <gperftools/tcmalloc.h>
#include <stdio.h>

int main(void)
{
	char *str = tc_valloc(1024);
	printf("%s\n", str);
	tc_free(str);
	return 0;
}

