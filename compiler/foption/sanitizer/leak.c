#include <malloc.h>
#include <string.h>
#include <unistd.h>

int malloc_leak(void)
{
	char *a = (char *)malloc(10);
	char *b = (char *)malloc(10);

	(void)b;
	free(a);
	/* leak b */

	return 0;
}

int main(void)
{
	malloc_leak();
	return 0;
}
