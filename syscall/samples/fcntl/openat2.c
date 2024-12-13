#include <stdio.h>
#include <errno.h>
#include <fcntl.h>
#include <stdbool.h>
#include <string.h>
#include <syscall.h>
#include <limits.h>
#include <unistd.h>
#include <sys/syscall.h>
#include <sys/types.h>
#include <sys/stat.h>

#include <linux/version.h>

bool openat2_supported = false;

/**
 * linux commit fddb5d430ad9 ("open: introduce openat2(2) syscall") is
 * v5.5-rc1-11-gfddb5d430ad9.
 */
#if LINUX_VERSION_CODE >= KERNEL_VERSION(5, 5, 0)
#include <linux/openat2.h>

bool needs_openat2(const struct open_how *how)
{
	return how->resolve != 0;
}

int raw_openat2(int dfd, const char *path, void *how, size_t size)
{
	int ret = syscall(__NR_openat2, dfd, path, how, size);
	return ret >= 0 ? ret : -errno;
}

int sys_openat2(int dfd, const char *path, struct open_how *how)
{
	return raw_openat2(dfd, path, how, sizeof(*how));
}

int sys_openat(int dfd, const char *path, struct open_how *how)
{
	int ret = openat(dfd, path, how->flags, how->mode);
	return ret >= 0 ? ret : -errno;
}

void __attribute__((constructor)) init(void)
{
	struct open_how how = { };
	int fd;

	/* Check openat2(2) support. */
	fd = sys_openat2(AT_FDCWD, ".", &how);
	openat2_supported = (fd >= 0);

	if (fd >= 0)
		close(fd);
}
#endif

int main(void)
{
	int fd1, fd2;
	struct open_how how = { };

	printf("openat2(2) %s\n", openat2_supported ? "supported" : "unsupported");

	fd1 = sys_openat2(AT_FDCWD, ".", &how);
	fd2 = sys_openat2(AT_FDCWD, "..", &how);

	close(fd1);
	close(fd2);
	return 0;
}
