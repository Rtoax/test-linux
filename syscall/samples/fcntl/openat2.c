#include <stdio.h>
#include <errno.h>
#include <fcntl.h>
#include <string.h>
#include <stdbool.h>
#include <syscall.h>
#include <limits.h>
#include <unistd.h>
#include <sys/syscall.h>
#include <sys/types.h>
#include <sys/stat.h>

#include "fcntl_helpers.h"

int main(void)
{
	int fd1, fd2;
	struct open_how how = { };

	printf("openat2(2) %s\n", support_openat2() ? "supported" : "unsupported");

	/**
	 * TODO: Test flags and mode
	 */
	how.flags = O_RDWR;
	how.mode = 0600;

	fd1 = sys_openat2(AT_FDCWD, ".", &how, sizeof(how));
	fd2 = sys_openat2(AT_FDCWD, "..", &how, sizeof(how));

	close(fd1);
	close(fd2);
	return 0;
}
