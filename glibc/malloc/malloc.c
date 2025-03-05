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
	return 0;
}
