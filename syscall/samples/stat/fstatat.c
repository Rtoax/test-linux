#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>
#include "stat_helpers.h"
#include "proc_helpers.h"

int main(int argc, char *argv[])
{
	int dirfd;
	struct stat buf;
	char *file = "/etc/os-release";

	dirfd = openat(AT_FDCWD, ".", O_RDONLY | O_CLOEXEC);

	proc_pid_fds_display(getpid());

	fstatat(dirfd, argv[0], &buf, AT_SYMLINK_NOFOLLOW);
	print_stat(argv[0], &buf);

	fstatat(dirfd, file, &buf, AT_SYMLINK_NOFOLLOW);
	print_stat(file, &buf);

	close(dirfd);
	return 0;
}
