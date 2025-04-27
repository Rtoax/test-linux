#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <strings.h>
#include <sys/stat.h>

#include "stat_helpers.h"
#include "proc.h"


int main(int argc, char *argv[])
{
	int fd;
	struct stat buf;
	char *filename = "/etc/os-release";

	if (argc > 1)
		filename = argv[1];

	if (!strcasecmp(filename, "cwd"))
		filename = NULL;

	if (filename)
		fd = open(filename, O_RDONLY);
	else
		fd = AT_FDCWD;

	fstat(fd, &buf);
	print_stat(filename, &buf);

	sys_fstat(fd, &buf);
	print_stat(filename, &buf);

	proc_pid_fds_display(getpid());

	close(fd);

	return 0;
}
