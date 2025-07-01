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
#include <sys/epoll.h>
#include <linux/version.h>

#include "epoll_helpers.h"

#if !defined(__aarch64__) && !defined(__riscv) && !defined(__loongarch64)
int sys_epoll_wait(int epfd, struct epoll_event *events, int maxevents,
		   int timeout)
{
	return syscall(__NR_epoll_wait, epfd, events, maxevents, timeout);
}
#endif

int sys_epoll_pwait(int epfd, struct epoll_event *events, int maxevents,
		    int timeout, const sigset_t *sigmask)
{
	return syscall(__NR_epoll_pwait, epfd, events, maxevents, timeout, sigmask);
}

/**
 * kernel commit 58169a52ebc9 ("epoll: add syscall epoll_pwait2")
 * v5.10-11840-g58169a52ebc9
 */
#if LINUX_VERSION_CODE >= KERNEL_VERSION(5, 10, 0)
int sys_epoll_pwait2(int epfd, struct epoll_event *events, int maxevents,
		     const struct timespec *timeout, const sigset_t *sigmask)
{
#ifndef __NR_epoll_pwait2
#define __NR_epoll_pwait2	441
#endif
	return syscall(__NR_epoll_pwait2, epfd, events, maxevents, timeout, sigmask);
}
#endif
