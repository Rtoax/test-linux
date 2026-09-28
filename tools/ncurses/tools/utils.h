// SPDX-License-Identifier: (LGPL-2.1 OR BSD-2-Clause)
/* Copyright (C) 2026 Rong Tao. All rights reserved. */
#pragma once
#include <sys/time.h>

struct select_fds {
	int maxfd;
	fd_set fds;
};

#define ARRAY_SIZE(arr) (sizeof(arr) / sizeof(arr[0]))

unsigned long usecs(void);
const char *timeval_str(struct timeval *tv, char buf[32]);
struct timeval max_timeval(struct timeval *tv1, struct timeval *tv2);
struct timeval diff_timeval(struct timeval *tv1, struct timeval *tv2);

unsigned long str2nsecs(const char *str);

long alloc_buf_read_file(const char *filename, char **buf);

int new_timerfd(unsigned long nsecs);

void select_fds_zero(struct select_fds *fds);
void select_fds_add(struct select_fds *fds, int fd);
int select_fd(struct select_fds *fds, fd_set *active);
