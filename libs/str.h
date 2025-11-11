#pragma once

void *memcpy_c(void *dest, const void *src, size_t n);
char *strcaseswap(char *str, ssize_t len);
char *vstrjoint(char *dst, const char *fmt, ...);
const char *vstrcat(int nstr, ...);
const char *vstrcat_r(char buf[], int nstr, ...);

unsigned long str2size(const char *str);
