#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

#if defined(DEV_INPUT_MOUSE0)
# define DEV	"/dev/input/mouse0"
#else
# define DEV	"/dev/input/mice"
#endif

int main(void)
{
	int fd;
	char buf[6];

	if ((fd = open("/dev/input/mouse0", O_RDONLY)) < 0) {
		perror("open(2)");
		exit(1);
	}

	fprintf(stderr, "Move your mouse to see what happen!!!\n");

	while (1) {
		read(fd, buf, 6);
		printf("%-8d: (%-8d, %-8d)\n", buf[0], buf[1], buf[2]);
	}
	close(fd);

	return 0;
}
