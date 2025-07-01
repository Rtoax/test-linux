// SPDX-License-Identifier: (LGPL-2.1 OR BSD-2-Clause)
#pragma once

#include <sys/epoll.h>

int sys_epoll_wait(int epfd, struct epoll_event *events, int maxevents,
		   int timeout);
int sys_epoll_pwait(int epfd, struct epoll_event *events, int maxevents,
		    int timeout, const sigset_t *sigmask);
int sys_epoll_pwait2(int epfd, struct epoll_event *events, int maxevents,
		     const struct timespec *timeout, const sigset_t *sigmask);
