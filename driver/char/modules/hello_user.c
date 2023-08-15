#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>


#define DEV_NAME	"/dev/hello"

int main(void)
{
	int fd;
	int val=1;

	fd = open(DEV_NAME, O_RDWR);
	if (fd < 0) {
		printf("test: can't open %s \n", DEV_NAME);
		exit(1);
	}

	write(fd, &val, 4);

	read(fd, &val, 4);

	return 0;
}