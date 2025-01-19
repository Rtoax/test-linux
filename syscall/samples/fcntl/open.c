#include <stdio.h>
#include <errno.h>
#include <fcntl.h>
#include <string.h>
#include <syscall.h>
#include <unistd.h>
#include <sys/syscall.h>
#include <sys/types.h>

#if !defined(__aarch64__) && !defined(__riscv)
/* FIXME: stdarg??? */
int sys_open_fm(const char *pathname, int flags, mode_t mode)
{
	return syscall(__NR_open, pathname, flags, mode);
}

int sys_open_f(const char *pathname, int flags)
{
	return syscall(SYS_open, pathname, flags);
}
#endif

int main(void)
{
	int fd;
	mode_t mode;
	char *path;

	path = "tmp.txt";

	unlink(path);
	/**
	 * flag make file could not exist.
	 */
	mode = S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH;

	printf("%04o\n", mode);

	fd = open(path, O_WRONLY | O_EXCL | O_CREAT, mode);
	if (fd == -1) {
		perror("open");
		return 1;
	}
	close(fd);
	return 0;
}
