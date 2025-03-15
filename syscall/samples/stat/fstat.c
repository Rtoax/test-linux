#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>

#include "helpers.h"
#include "proc.h"


int main(void)
{
	struct stat buf;

	int fd = open("/etc/os-release", O_RDONLY);

	fstat(fd, &buf);
	print_stat(&buf);

	sys_fstat(fd, &buf);
	print_stat(&buf);

	proc_pid_fds_display(getpid());

	return 0;
}
