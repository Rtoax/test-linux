// SPDX-License-Identifier: GPL-2.0
// Copyright (C) 2026 Rong Tao
#include <stddef.h>
#include <sys/time.h>

unsigned long usecs(void)
{
	struct timeval tv;
	gettimeofday(&tv, NULL);
	return tv.tv_sec * 10e6 + tv.tv_usec;
}
