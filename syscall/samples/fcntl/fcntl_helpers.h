#pragma once

#include <sys/types.h>
#include <linux/types.h>
#include <linux/version.h>
#if LINUX_VERSION_CODE >= KERNEL_VERSION(5, 5, 0)
#include <linux/openat2.h>
#else
struct open_how {
	__u64 flags;
	__u64 mode;
	__u64 resolve;
};
#endif

int sys_open_fm(const char *pathname, int flags, mode_t mode);
int sys_open_f(const char *pathname, int flags);

int sys_openat(int dfd, const char *path, int flags, mode_t mode);

int support_openat2(void);
int sys_openat2(int dfd, const char *path, const struct open_how *how,
		size_t size);

/* file lock */
void tl_fwrlock(int fd, int wait);
void tl_funlock(int fd);
