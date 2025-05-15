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
	 *
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
	printf("__STDC_VERSION__ %ld\n", __STDC_VERSION__);

#ifdef __cplusplus
# if __cplusplus != __STDC_VERSION__
#  pragma message "__cplusplus != __STDC_VERSION__"
# endif
#endif


#ifdef __OBJC__
	/* This macro is defned, with value 1, when the Objective-C compiler is
	 * in use. You can use __OBJC__ to test whether a header is compiled by
	 * a C compiler or an Objective-C compiler. */
	printf("__OBJC__ %d\n", __OBJC__);
#endif
	return 0;
}
