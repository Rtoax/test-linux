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

	printf("O_CREAT : %0o\n", O_CREAT);

	/**
	 * flags make file could not exist.
	 */
	flags = O_WRONLY | O_EXCL | O_CREAT;
	mode = S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH;

	printf("file = %s\n", path);
	printf("flags = %08o\n", flags);
	printf("mode  = %04o\n", mode);

#if defined(SYS_OPENAT)
	fd = sys_openat(AT_FDCWD, path, flags, mode);
#else
	fd = sys_open_fm(path, flags, mode);
#endif
	if (fd == -1) {
		perror("open");
		return 1;
	}
	close(fd);
	return 0;
}
