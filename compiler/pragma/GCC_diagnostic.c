/**
 * See also
 *
 * linux include/linux/compiler-gcc.h
 *   #define __diag_str1(s)          #s
 *   #define __diag_str(s)           __diag_str1(s)
 *   #define __diag(s)               _Pragma(__diag_str(GCC diagnostic s))
 *
 * linux include/linux/compiler-clang.h
 *   #define __diag_str1(s)          #s
 *   #define __diag_str(s)           __diag_str1(s)
 *   #define __diag(s)               _Pragma(__diag_str(clang diagnostic s))
 */

#include <stdio.h>

#if defined(__clang__)
# pragma clang diagnostic push
#elif defined(__GNUC__)
# pragma GCC diagnostic push
#endif
/* Couldn't ignore -pg,
 * error: ‘-pg’ is not an option that controls warnings */
#if defined(__clang__)
# pragma clang diagnostic ignored "-pg"
#elif defined(__GNUC__)
# pragma GCC diagnostic ignored "-pg"
#endif
void foo(void)
{
	return;
}
#if defined(__clang__)
# pragma clang diagnostic pop
#elif defined(__GNUC__)
# pragma GCC diagnostic pop
#endif

int main(void)
{
	int i;
#if defined(__clang__)
# pragma clang diagnostic push
//# pragma clang diagnostic ignored "-Wmaybe-uninitialized"
# pragma clang diagnostic ignored "-Wuninitialized"
# pragma clang diagnostic ignored "-Wunused-variable"
#elif defined(__GNUC__)
# pragma GCC diagnostic push
# pragma GCC diagnostic ignored "-Wmaybe-uninitialized"
# pragma GCC diagnostic ignored "-Wuninitialized"
# pragma GCC diagnostic ignored "-Wunused-variable"
# if __GNUC__ >= 11 && __GNUC_MINOR__ >= 1
/* Ignore read(2) overflow and write(2) overread compile warnings */
#  pragma GCC diagnostic ignored "-Wstringop-overread"
#  pragma GCC diagnostic ignored "-Wstringop-overflow"
# endif
#endif
	printf("%d\n", i);
#if defined(__clang__)
# pragma clang diagnostic pop
#elif defined(__GNUC__)
# pragma GCC diagnostic pop
#endif
	printf("%d\n", i);
	return 0;
}
