#include <stdio.h>
#include <errno.h>
#include <fcntl.h>
#include <string.h>
#include <syscall.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/syscall.h>
#include <sys/types.h>

int main(void)
{
	int fd, ret;
	char buf[32];
	struct stat stat;

	/**
	 * The file itself is not opened
	 */
	fd = open("/etc/os-release", O_PATH);
	if (fd == -1) {
		perror("open");
		return 1;
	}

	ret = read(fd, buf, 2);
	if (ret > 0 || errno != EBADF) {
		fprintf(stderr, "read must return EBADF if open with O_PATH.\n");
	}

	ret = fstat(fd, &stat);
	if (ret) {
		fprintf(stderr, "fstat could use if open with O_PATH.\n");
	}
	printf("size = %ld\n", stat.st_size);

	close(fd);
	return 0;
}
