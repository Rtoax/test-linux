#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <unistd.h>

int main(void)
{
	char *s = memalign(getpagesize(), 123);
	printf("%d: %p\n", getpagesize(), s);
	free(s);
	return 0;
}
