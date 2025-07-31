/**
 * C Standard
 * ============================================================================
 * Name		Year	GCC	CFLAGS
 * C89(ANSI C)	1989		-std=c89
 * GNU C89	1989		-std=gnu89	(linux)
 * C90(ISO C)	1990		-std=c90
 * C90(ISO C)	1990		-std=iso9899:1990
 * GNU C90	1990		-std=gnu90
 * C99		1999		-std=c99
 * GNU C99	1999		-std=gnu99
 * C11		2011	4.7+	-std=c11
 * GNU C11	2011		-std=gnu11
 * C17(C18)	2018	8+	-std=c17
 * GNU C17	2018		-std=gnu17
 * C23(C2x)	2024		-std=c23
 * GNU C23	2024	13+	-std=gnu23
 *
 * C++ Standard
 * ============================================================================
 * Name		Year	GCC	CFLAGS		__cplusplus
 * C++98	1998		-std=c++98	199711L
 * GNU C++98	1998		-std=gnu++98	199711L
 * C++03	2003		-std=c++03
 * GNU C++03	2003		-std=gnu++03
 * C++11(C++0x)	2011	4.8+	-std=c++11
 * GNU C++11	2011		-std=gnu++11
 * C++14(C++1y)	2014	5+	-std=c++14
 * GNU C++14	2014		-std=gnu++14
 * C++17(C++1z)	2017	7+	-std=c++17
 * GNU C++17	2017		-std=gnu++17
 * C++20(C++2a)	2020	11+	-std=c++20
 * GNU C++20	2020		-std=gnu++20
 * C++23(C++2b)	2023		-std=c++23
 * GNU C++23	2023		-std=gnu++23
 * C++26	2026*		-std=c++26	dev
 *
 * vim:ts=8
 */
#include <stdio.h>

int main(void)
{
	printf("__STDC__ %d\n", __STDC__);

	/* This macro is defned, with value 1, if the compiler’s target is a
	 * hosted environment. A hosted environment has the complete facilities
	 * of the standard C library available. */
	printf("__STDC_HOSTED__ %d\n", __STDC_HOSTED__);

	/* This macro expands to the C Standard’s version number, a long integer
	 * constant of the form yyyymmL where yyyy and mm are the year and month
	 * of the Standard version. This signifes which version of the C
	 * Standard the compiler conforms to. Like __STDC__, this is not
	 * necessarily accurate for the entire implementation, unless GNU CPP is
	 * being used with GCC.
	 * The value 199409L signifes the 1989 C standard as amended in 1994,
	 * which is the current default; the value 199901L signifes the 1999
	 * revision of the C standard. Support for the 1999 revision is not yet
	 * complete.
	 * This macro is not defned if the ‘-traditional-cpp’ option is used,
	 * nor when compiling C++ or Objective-C.
	 */
#ifdef __cplusplus
	/**
	 * C++98: 199711L
	 * C++03: 199711L (same as C++98)
	 * C++11: 201103L
	 * C++14: 201402L
	 * C++17: 201703L
	 * C++20: 202002L
	 * C++23: 202302L
	 * C++23: 202302L (not exist yet)
	 *
	 * Example: -std=c++98
	 */
	printf("__cplusplus %ld\n", __cplusplus);
#endif
	/**
	 * FIXME: Why __STDC_VERSION__ not defined
	 */
#if defined(__STDC_VERSION__) || \
	(!defined(__cplusplus) && !defined(STD_C98) && !defined(STD_GNU98) && !defined(STD_C17))
	printf("__STDC_VERSION__ %ld\n", __STDC_VERSION__);
#endif

#ifdef __OBJC__
	/* This macro is defned, with value 1, when the Objective-C compiler is
	 * in use. You can use __OBJC__ to test whether a header is compiled by
	 * a C compiler or an Objective-C compiler. */
	printf("__OBJC__ %d\n", __OBJC__);
#endif

#ifdef __NVCC__
	printf("__NVCC__ = %d\n", __NVCC__);
#endif

	return 0;
}
