#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/syscall.h>
#include <syscall.h>
#include <unistd.h>
#include <errno.h>
#include <fcntl.h>

#include "stat_helpers.h"


int do_statx(int dfd, const char *path, int flags, unsigned mask,
	     struct statx *statxbuf)
{
	return syscall(__NR_statx, dfd, path, flags, mask, statxbuf);
}

int main(int argc, char *argv[])
{
	int err;
	struct statx buf;
	const char *filename = "/etc/os-release";

	if (argc >= 2)
		filename = argv[1];

	err = statx(AT_FDCWD, filename, 0, STATX_ALL, &buf);
	if (err) {
		perror("statx");
		return -errno;
	}

	print_statx(&buf);

	if (buf.stx_mode & S_IWUSR)
		printf("Owning user can write `%s'.\n", filename);

	return 0;
}
