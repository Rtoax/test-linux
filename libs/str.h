// SPDX-License-Identifier: (LGPL-2.1 OR BSD-2-Clause)
#pragma once

void *memcpy_c(void *dest, const void *src, size_t n);
char *strcaseswap(char *str, ssize_t len);
char *vstrjoint(char *dst, const char *fmt, ...);
const char *vstrcat(int nstr, ...);
const char *vstrcat_r(char buf[], int nstr, ...);

unsigned long str2size(const char *str);
unsigned long str2nsecs(const char *str);
