#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <mcheck.h>
#include <unistd.h>

int main(void)
{
	char *str;
	size_t size = getpagesize();

	str = malloc(size);
	mtrace();

#ifdef OVERFLOW
#pragma message("test overflow")
	/**
	 * $ valgrind --tool=memcheck ./overflow
	 */
	str[size] = 'a';
#endif

	free(str);
#ifdef DOUBLE_FREE
#pragma message("test double-free")
	/**
	 * $ valgrind --tool=memcheck ./double-free
	 */
	free(str);
#endif

#ifdef USE_AFTER_FREE
#pragma message("test use-after-free")
	/**
	 * $ valgrind --leak-check=full ./use-after-free
	 */
	str[1] = 'c';
#endif

	return 0;
}
