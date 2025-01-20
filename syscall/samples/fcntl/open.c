#include <stdio.h>
#include <errno.h>
#include <fcntl.h>
#include <string.h>
#include <syscall.h>
#include <unistd.h>
#include <sys/syscall.h>
#include <sys/types.h>

#include "helpers.h"

int main(void)
{
	int fd, flags;
	mode_t mode;
	char *path;

	path = "tmp.txt";

	unlink(path);

	flags = O_WRONLY | O_EXCL | O_CREAT;
	/**
	 * flag make file could not exist.
	 */
	mode = S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH;

	printf("flags = %08o\n", flags);
	printf("mode  = %04o\n", mode);

	fd = open(path, flags, mode);
	if (fd == -1) {
		perror("open");
		return 1;
	}
	close(fd);
	return 0;
}
