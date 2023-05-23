#pragma once

#include <stdio.h>
#include <malloc.h>
#include <string.h>

#ifndef CACHE_LINE_SIZE
# warning "Need define CACHE_LINE_SIZE=?, use default 64"
#define CACHE_LINE_SIZE 64
#endif
#define __cacheline_size	CACHE_LINE_SIZE

#define __cacheline_align	__attribute__ ((aligned (__cacheline_size)))
#define __noinline	__attribute__ ((noinline))

#ifdef NOLIKELY
#define likely(x) x
#define unlikely(x) x
#else
#define likely(x)    __builtin_expect(!!(x), 1)
#define unlikely(x)  __builtin_expect(!!(x), 0)
#endif

#if defined (__GNUC__) && !defined (__clang__)
# define __opt_O0 __attribute__((optimize("-O0")))
#elif defined (__clang__)
/* FIXME */
# define __opt_O0
#else
# define __opt_O0
#endif

#define PAD_FN(name)	\
	unsigned long __opt_O0 __noinline	\
	f_pad_##name(unsigned long v) {	\
		unsigned long a, b, c, d, e, f, g;	\
		a = b = c = d = e = f = g = 123;	\
		char *sa, *sb, *sc, *sd;	\
		sa = sb = sc = sd = "Hello";	\
		sa = malloc(123);	\
		sb = malloc(123);	\
		memcpy(sa, sb, 123);	\
		free(sa);	\
		free(sb);	\
		return 0;	\
	}

void start(void);
void stop(void);
void swap_int(int *a, int *b);
void set_rand_value(int *i);
void rand_array(int *arr, int arr_len);
