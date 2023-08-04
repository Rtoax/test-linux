#include <fcntl.h> /* Definition of AT_* constants */
#include <unistd.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <sys/syscall.h>


/* No glibc swapper */
int sys_faccessat2(int dirfd, const char *pathname, int mode, int flags)
{
#if defined(SYS_faccessat2)
	return syscall(SYS_faccessat2, dirfd, pathname, mode, flags);
#else
	errno = -ENOSYS;
	return -1;
#endif
}

int main(void)
{
	int ret;

	ret = sys_faccessat2(AT_FDCWD, "/etc/os-release", F_OK, AT_EACCESS);
	if (ret != 0) {
		fprintf(stderr, "faccessat2 failed: %s\n", strerror(errno));
	}

	return 0;
}

