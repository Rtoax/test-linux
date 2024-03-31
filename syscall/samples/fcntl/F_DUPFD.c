#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>


int main(void)
{
	int fd = fcntl(fileno(stdout), F_DUPFD);
	if (fd <= 0) {
		fprintf(stderr, "fcntl: F_DUPFD: %m\n");
		exit(1);
	}
	write(fd, "Hello", 6);
	return 0;
}
