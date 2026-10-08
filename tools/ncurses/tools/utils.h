// SPDX-License-Identifier: (LGPL-2.1 OR BSD-2-Clause)
/* Copyright (C) 2026 Rong Tao. All rights reserved. */
#pragma once
#include <sys/time.h>

#define ARRAY_SIZE(arr) (sizeof(arr) / sizeof(arr[0]))
#define KiB 1024
#define MiB (1024 * KiB)
#define GiB (1024 * MiB)
#define TiB (1024 * GiB)

unsigned long usecs(void);
unsigned long nsecs(void);

const char *timeval_str(struct timeval *tv, char buf[32]);
struct timeval max_timeval(struct timeval *tv1, struct timeval *tv2);
struct timeval diff_timeval(struct timeval *tv1, struct timeval *tv2);

unsigned long str2nsecs(const char *str);
unsigned long str2size(const char *str);

long alloc_buf_read_file(const char *filename, char **buf);

int new_timerfd(unsigned long nsecs);
