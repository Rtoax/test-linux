#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include <fcntl.h>

int grantpt(int fd);

int main(void)
{
	int fd = open("/dev/ptmx", 0x1111);
	grantpt(fileno(stdout));
	perror("grantpt");
	close(fd);
	return 0;
}
