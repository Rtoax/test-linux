#include <stdio.h>
#include <errno.h>
#include <fcntl.h>
#include <unistd.h>
#include <syscall.h>

void sys_sync(void)
{
	syscall(SYS_sync);
}

int sys_syncfs(int fd)
{
	return syscall(SYS_syncfs, fd);
}

int main(void)
{
	int fd, ret;
	mode_t mode;
	char *path;

	path = "tmp.txt";

	mode = S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH;
	fd = open(path, O_WRONLY | O_EXCL | O_CREAT, mode);
	if (fd == -1) {
		perror("open");
		return 1;
	}

	sync();
	ret = syncfs(fd);
	if (ret) {
		fprintf(stderr, "syncfs: %m\n");
	}

	close(fd);

	return 0;
}
