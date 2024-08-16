#include <unistd.h>
#include <stdio.h>
#include <errno.h>
#include <linux/memfd.h>
#include <sys/syscall.h>
#include <sys/mman.h>


int sys_memfd_create(const char *name, unsigned int flags)
{
	int fd;

#if __GLIBC__ == 2 && __GLIBC_MINOR__ >= 26
	fd = memfd_create(name, flags);
#else
	fd = syscall(__NR_memfd_create, name, flags);
#endif
	if (fd == -1) {
		fprintf(stderr, "memfd_secret: %m\n");
		return -errno;
	}
	return fd;
}

int sys_memfd_secret(unsigned int flags)
{
	int fd;

	fd = syscall(SYS_memfd_secret, flags);
	if (fd == -1) {
		fprintf(stderr, "memfd_secret: %m\n");
		return -errno;
	}
	return fd;
}
