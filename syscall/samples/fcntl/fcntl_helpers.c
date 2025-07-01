// SPDX-License-Identifier: (LGPL-2.1 OR BSD-2-Clause)
#include <stdio.h>
#include <stdbool.h>
#include <errno.h>
#include <fcntl.h>
#include <string.h>
#include <syscall.h>
#include <unistd.h>
#include <sys/syscall.h>
#include <sys/types.h>
#include <linux/version.h>

#include "fcntl_helpers.h"

#if !defined(__aarch64__) && !defined(__riscv) && !defined(__loongarch64)
/* FIXME: stdarg??? */
int sys_open_fm(const char *pathname, int flags, mode_t mode)
{
	return syscall(__NR_open, pathname, flags, mode);
}

int sys_open_f(const char *pathname, int flags)
{
	return syscall(__NR_open, pathname, flags);
}
#else
int sys_open_fm(const char *pathname, int flags, mode_t mode)
{
	return -ENOSYS;
}

int sys_open_f(const char *pathname, int flags)
{
	return -ENOSYS;
}
#endif

int sys_openat(int dfd, const char *path, int flags, mode_t mode)
{
	return syscall(__NR_openat, dfd, path, flags, mode);
}

/**
 * linux commit fddb5d430ad9 ("open: introduce openat2(2) syscall") is
 * v5.5-rc1-11-gfddb5d430ad9.
 */
#if LINUX_VERSION_CODE >= KERNEL_VERSION(5, 5, 0)
bool needs_openat2(const struct open_how *how)
{
	return how->resolve != 0;
}

/* const struct open_how *how */
int sys_openat2(int dfd, const char *path, const struct open_how *how,
		size_t size)
{
	int ret = syscall(__NR_openat2, dfd, path, how, size);
	return ret >= 0 ? ret : -errno;
}

int support_openat2(void)
{
	struct open_how how = { };
	int fd, ret;

	fd = sys_openat2(AT_FDCWD, ".", &how, sizeof(how));
	ret = (fd >= 0);
	if (fd >= 0)
		close(fd);
	return ret;
}
#else
int sys_openat2(int dfd, const char *path, const struct open_how *how,
		size_t size)
{
	return -ENOSYS;
}

int support_openat2(void)
{
	return 0;
}
#endif

void tl_fwrlock(int fd, int wait)
{
	struct flock lock;
	int op;

	/**
	 * F_SETLKW: As for F_SETLK, but if a conflicting lock is held on the
	 * file, then wait for that lock to be released.
	 */
	op = wait ? F_SETLKW : F_SETLK;

	memset(&lock, 0, sizeof(lock));

	lock.l_type = F_WRLCK;
	lock.l_whence = SEEK_SET;
	lock.l_start = 0;
	/* 0: write lock entire file */
	lock.l_len = 0;

	fcntl(fd, op, &lock);
}

void tl_funlock(int fd)
{
	struct flock lock;

	memset(&lock, 0, sizeof(lock));

	lock.l_type = F_UNLCK;
	lock.l_whence = SEEK_SET;
	lock.l_start = 0;
	/* 0: unlock entire file */
	lock.l_len = 0;

	fcntl(fd, F_SETLK, &lock);
}
