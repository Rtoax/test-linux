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

int main(void)
{
	/* allocate memory that is automatically freed */
	char *str = alloca(256);
	(void)str;
	return 0;
}
