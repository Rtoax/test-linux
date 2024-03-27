#include <stdio.h>
#include <errno.h>
#include <fcntl.h>
#include <string.h>
#include <syscall.h>
#include <unistd.h>
#include <sys/syscall.h>
#include <sys/types.h>

#if !defined(__aarch64__)
int sys_open(const char *pathname, int flags, mode_t mode)
{
	return syscall(__NR_open, pathname, flags, mode);
}
#endif

int main(void)
{
	char *path = "tmp.txt";
	mode_t mode = S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH;
	int fd = open(path, O_WRONLY | O_EXCL | O_CREAT, mode);
	if (fd == -1) {
		perror("open");
		return 1;
	}
	close(fd);
	return 0;
}
