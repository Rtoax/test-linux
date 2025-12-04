#include <stdio.h>
#include <malloc.h>
#include <unistd.h>

#if defined(__aarch64__)
extern void __aarch64_sync_cache_range(void *, void *);
# define flush_cache(start, end) __aarch64_sync_cache_range(start, end)
#else
# define flush_cache(start, end) __builtin___clear_cache(start, end)
#endif

int main(void)
{
	size_t i, size = getpagesize() * 1024;
	char *str = malloc(size);

	/* Maybe generate lots of Cache */
	for (i = 0; i < size; i += getpagesize()) {
		str[i] = 'a';
	}

	/* Flushing */
	flush_cache(str, str + size - 1);

	free(str);
	return 0;
}
