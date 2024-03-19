#include <stdio.h>
#include <malloc.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>


char *gnu_getcwd(void)
{
	size_t size = 100;

	while (1) {
		char *buffer = (char *)malloc(size);
		if (getwd(buffer) == buffer)
			return buffer;
		free(buffer);
		if (errno != ERANGE)
			return 0;
		size *= 2;
	}
}

int main(void)
{
	printf("%s\n", gnu_getcwd());

	return 0;
}
