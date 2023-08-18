#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <unistd.h>
#include <assert.h>
#include <sys/mman.h>


int main(void)
{
	size_t i;
	size_t page_size;
	int alloc_size;
	char *mem = NULL;


	if (mlockall(MCL_CURRENT | MCL_FUTURE)) {
		perror("mlockall failed.");
		assert(0);
	}

	page_size = getpagesize();
	alloc_size = 1024 * page_size;
	mem = malloc(alloc_size);
	assert(mem);

	for (i = 0; i < alloc_size; i += page_size)
		mem[i] = 0;

	munlock(mem, alloc_size);
	free(mem);

	return 0;
}