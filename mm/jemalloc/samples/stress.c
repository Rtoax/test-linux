#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>
#include <jemalloc/jemalloc.h>

int main(void)
{
	int i;
	char *mem;
	size_t nbytes;
	size_t pagesize;

	nbytes = 102400;
	pagesize = getpagesize();

	printf("Page size %ld\n", pagesize);

	while (1) {
		mem = malloc(nbytes);

		/* Page fault */
		for (i = 0; i < nbytes; i += pagesize)
			mem[i] = 'a';
		memset(mem, 0xEF, nbytes);

		free(mem);
	}

	return 0;
}
