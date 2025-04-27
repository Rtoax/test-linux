#include <stdio.h>
#include <ctype.h>

void display_argv(int argc, char *argv[], int seperator, int end)
{
	int i;
	for (i = 0; i < argc; i++) {
		printf("argv[%i] = %s%c", i, argv[i],
			isprint(seperator) ? seperator : '\n');
	}
	printf("%c", isprint(end) ? end : '\n');
}

