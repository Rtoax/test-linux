#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/mman.h>
#include <jemalloc/jemalloc.h>

void disable_retain(void)
{
	size_t size = sizeof(size_t);
	size_t old, value;

	old = 0;
	mallctl("stats.retained", &old, &size, NULL, 0);
	printf("stats.retained = %ld bytes, %ld MB\n", old, old / 1024 / 1024);

	old = 0;
	mallctl("stats.mapped", &old, &size, NULL, 0);
	printf("stats.mapped = %ld bytes, %ld MB\n", old, old / 1024 / 1024);

	old = 0;
	mallctl("stats.arenas.0.retained", &old, &size, NULL, 0);
	printf("stats.arenas.0.retained = %ldbytes, %ld MB\n",
		old, old / 1024 / 1024);

	mallctl("stats.arenas.0.destroy", NULL, NULL, NULL, 0);

	/**
	 * FIXME: Try to turn off stats, but it's not works
	 */
	old = 0;
	value = 0;
	mallctl("config.stats", &old, &size, &value, size);
	printf("config.stats = %ld\n", old);

	/**
	 * Disable retain
	 */
	value = 0;
	mallctl("config.malloc_conf.retain", &old, &size, &value, size);
	printf("config.malloc_conf.retain = %ld\n", old);
}

int main(void)
{
	int i;
	char *mem;
	size_t nbytes;
	size_t pagesize;

	mlockall(MCL_CURRENT | MCL_ONFAULT);

	nbytes = 102400;
	pagesize = getpagesize();

	disable_retain();

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
