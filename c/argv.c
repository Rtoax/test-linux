#include <stdio.h>

/**
 * Pass parameters.
 *
 * $ opts=( --define "a b c" )
 * $ ./argv "${opts[@]}"
 */
int main(int argc, char *argv[])
{
	int i;
	for (i = 0; i < argc; i++)
		printf("argv[%d] = %s\n", i, argv[i]);
	return 0;
}
