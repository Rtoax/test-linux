#ifndef _GNU_SOURCE
#define _GNU_SOURCE
#endif
#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

int main(void)
{
	int ret;
	char file[256] = {"/tmp/key-XXXXXX"};

	printf("file: %s\n", file);
	ret = mkostemp(file, O_RDWR | O_CREAT);
	perror("mkostemp: ");
	printf("file: %s, ret = %d\n", file, ret);

	unlink(file);

	return 0;
}
