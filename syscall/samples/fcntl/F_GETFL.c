#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>


int tl_setnonblock(int fd)
{
	int flags;
	flags = fcntl(fd, F_GETFL);
	if (flags < 0) {
		perror("fcntl(sock, GETFL) error");
		return -errno;
	}
	flags = flags | O_NONBLOCK;
	if (fcntl(fd, F_SETFL, flags) < 0) {
		perror("fcntl(sock, SETFL, flags)");
		return -errno;
	}
	return 0;
}

int main(int argc, char* argv[])
{
	char *file = argv[1] ?: "a.txt";
	int fd;

	printf("opening %s\n", file);
	fd = open(file, O_CREAT | O_WRONLY, 0644);
	if (fd == -1) {
		fprintf(stderr, "open %s %m\n", file);
		exit(1);
	}

	tl_setnonblock(fd);

	close(fd);
	return 0;
}
