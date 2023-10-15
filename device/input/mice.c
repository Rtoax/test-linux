#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>


int main(void)
{
	int fd;
	char buf[6];

	if ((fd = open("/dev/input/mice", O_RDONLY)) < 0) {
		perror("open(2)");
		exit(1);
	}

	while (1) {
		read(fd, buf, 6);
		printf("%-8d: (%-8d, %-8d)\n",
			buf[0], buf[1], buf[2]);
	}
	close(fd);

	return 0;
}
