#include <gperftools/tcmalloc.h>
#include <stdio.h>

int main(void)
{
	char *str = tc_calloc(1024, 1);
	tc_cfree(str);
}
