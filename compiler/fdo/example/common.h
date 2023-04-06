#pragma once

#include <string.h>

#ifndef CACHE_LINE_SIZE
# error "You must define CACHE_LINE_SIZE=?"
#endif
#define __cacheline_size	CACHE_LINE_SIZE

#define __cacheline_align	__attribute__ ((aligned (__cacheline_size)))
#define __noinline	__attribute__ ((noinline))

#if defined (__GNUC__) && !defined (__clang__)
# define __opt_O0 __attribute__((optimize("-O0")))
#elif defined (__clang__)
/* FIXME */
# define __opt_O0
#else
# define __opt_O0
#endif

#if defined(CACHELINE_ALIGN) && !defined(NOINLINE)
#define __attr __cacheline_align
#elif defined(NOINLINE) && !defined(CACHELINE_ALIGN)
#define __attr __noinline
#elif defined(NOINLINE) && defined(CACHELINE_ALIGN)
#define __attr __cacheline_align __noinline
#else
#define __attr
#endif


#define FN(f)	__attr fdo_test_##f
#define CALL(f) fdo_test_##f

#define USELESS_FUNC_BODY \
	int __a, __b, __c; \
	char __s[256]; \
	memset(__s, 0, sizeof(256)); \
	do { \
		int i = strlen(__s); \
	} while (0);

#define DEFINE_FN_PAD(name) \
	void __cacheline_align \
	FN(name)(int *arr, int arr_len) { USELESS_FUNC_BODY; return; }

void FN(start)(void);
void FN(stop)(void);
void FN(swap_int)(int *a, int *b);
void FN(set_rand_value)(int *i);
void FN(rand_array)(int *arr, int arr_len);
