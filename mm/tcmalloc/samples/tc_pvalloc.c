#include <gperftools/tcmalloc.h>
#include <stdio.h>

int main(void)
{
	char *str = tc_pvalloc(1024);
	printf("%s\n", str);
	tc_free(str);
}


