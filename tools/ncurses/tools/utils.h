// SPDX-License-Identifier: (LGPL-2.1 OR BSD-2-Clause)
/* Copyright (C) 2026 Rong Tao */
#pragma once
#include <sys/time.h>

unsigned long usecs(void);
struct timeval max_timeval(struct timeval *tv1, struct timeval *tv2);

unsigned long str2nsecs(const char *str);

long alloc_buf_read_file(const char *filename, char **buf);
