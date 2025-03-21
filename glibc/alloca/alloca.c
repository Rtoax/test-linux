/**
 * alloca(3)
 *
 * The alloca() function allocates size bytes of space in the stack frame of
 * the caller.
 */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <alloca.h>
#include <fcntl.h>

int tl_open2(char *str1, char *str2, int flags, int mode)
{
	char *name = (char *)alloca(strlen(str1) + strlen(str2) + 1);
	stpcpy(stpcpy(name, str1), str2);
	return open(name, flags, mode);
}

int tl_open3(char *str1, char *str2, int flags, int mode)
{
	char *name = (char *)malloc(strlen(str1) + strlen(str2) + 1);
	int desc;
	if (name == 0)
		perror("virtual memory exceeded.");
	stpcpy(stpcpy(name, str1), str2);
	desc = open(name, flags, mode);
	free(name);
	return desc;
}

void stack_overflow(void)
{
	int i;
	size_t size = 102400000;
	char *str = alloca(size);

	/* Segmentation fault (core dumped) */
	for (i = 0; i < size; i += 4096)
		str[i] = '0';
}

int main(void)
{
	/* allocate memory that is automatically freed */
	char *str = alloca(256);
	/* no need to free */
	(void)str;
	stack_overflow();
	return 0;
}
