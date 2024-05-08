#ifndef _XOPEN_SOURCE
#define _XOPEN_SOURCE 1
#endif
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include <fcntl.h>


int main(void)
{
	int fd = open("/dev/ptmx", 0x1111);

	if (unlockpt(fd) < 0)
		printf("Unable to unlockpt: %m");
	if (grantpt(fd) < 0)
		printf("Unable to grantpt: %m");

	return 0;
}

