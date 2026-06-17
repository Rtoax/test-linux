#pragma once

#ifdef __has_include
#if __has_include(<quadmath.h>)
#include <quadmath.h>
#pragma message "compiler support quadmath.h"
#define HAVE_quadmath_h 1
#endif
#endif

#ifdef HAVE_quadmath_h
#define fp128_printf(fp128, tfmt)                                     \
	do {                                                          \
		char __buf[128];                                      \
		quadmath_snprintf(__buf, sizeof(__buf), tfmt, fp128); \
		printf(#fp128 " = %s\n", __buf);                      \
	} while (0)
#else
#define fp128_printf(fp128, tfmt)                                      \
	do {                                                           \
		fprintf(stderr, "Not support quadmath_snprintf(%s)\n", \
			#fp128);                                       \
	} while (0)
#endif

/**
 * GCC Additional Floating Types: https://gcc.gnu.org/onlinedocs/gcc/Floating-Types.html
 * - NVRTC on Linux
 * - GCC version 4.1 or later on x86_64/amd64
 * - Clang version 3.9 or later on x86_64/amd64
 * - NVHPC version 21.1 or later on x86_64/amd64
 */
#if (defined(__clang__) && (__clang_major__ >= 3 && __clang_minor__ >= 9)) || \
	(defined(__GNUC__) && (__GNUC__ >= 4))
#pragma message "Support __float128 arithmetic"
#define SUPPORT_FLOAT128_ARITHMETIC 1
#endif
