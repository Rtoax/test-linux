#define _XOPEN_SOURCE
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include <fcntl.h>

char *ptsname (int __fd);

int main(void)
{
	int fd = open("/dev/ptmx", 0x1111);
	printf("ptsname:%s\n", ptsname(fd));
	close(fd);

	return 0;
}

