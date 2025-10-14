#include <stdio.h>

extern char *__progname;

int main(void)
{
	printf("__progname.c: %s %p\n", __progname, __progname);
	return 0;
}
