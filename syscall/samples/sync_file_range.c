#include <stdio.h>
#include <errno.h>
#include <fcntl.h>
#include <unistd.h>
#include <syscall.h>

int sys_sync_file_range(int fd, off_t offset, off_t nbytes, unsigned int flags)
{
	return syscall(SYS_sync_file_range, fd, offset, nbytes, flags);
}

int main(void)
{
	int fd, ret;
	mode_t mode;
	char *path;

	path = "tmp.txt";

	unlink(path);

	/**
	 * flag make file could not exist.
	 */
	mode = S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH;
	fd = open(path, O_WRONLY | O_EXCL | O_CREAT, mode);
	if (fd == -1) {
		perror("open");
		return 1;
	}

	ret = sync_file_range(fd, 0, 32, SYNC_FILE_RANGE_WRITE);
	if (ret) {
		fprintf(stderr, "sync_file_range: %m\n");
	}

	close(fd);

	return 0;
}
