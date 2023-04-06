#pragma once

#include <string.h>

#ifndef CACHE_LINE_SIZE
# error "You must define CACHE_LINE_SIZE=?"
#endif
#define __cacheline_size	CACHE_LINE_SIZE

#if defined(CACHELINE_ALIGN)
# define __cacheline_align	__attribute__ ((aligned (__cacheline_size)))
#else
# warning "Not define CACHELINE_ALIGN"
# define __cacheline_align
#endif

#if defined(NOINLINE)
# define __noinline	__attribute__ ((noinline))
#else
# warning "Not define NOINLINE"
# define __noinline
#endif

#define __attr __cacheline_align __noinline


#define FN(f)	__attr fdo_test_##f

#define USELESS_FUNC_BODY \
	int __a, __b, __c; \
	char __s[256]; \
	memset(__s, 0, sizeof(256)); \
	do { \
		int i = strlen(__s); \
	} while (0);

#define DEFINE_FN_PAD(name) \
	void \
	FN(name)(int *arr, int arr_len) { USELESS_FUNC_BODY; return; }

void FN(start)(void);
void FN(stop)(void);
void FN(swap_int)(int *a, int *b);
void FN(set_rand_value)(int *i);
void FN(rand_array)(int *arr, int arr_len);
