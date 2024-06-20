#include <stdio.h>
#include <malloc.h>

#if defined(__aarch64__)
extern void __aarch64_sync_cache_range(void *, void *);
# define flush_cache(start, end) __aarch64_sync_cache_range(start, end)
#else
# define flush_cache(start, end) __builtin___clear_cache(start, end)
#endif

int main(void)
{
	char *str = malloc(sizeof(char) * 1024);
	flush_cache(str, str + 1024);
	free(str);
	return 0;
}
