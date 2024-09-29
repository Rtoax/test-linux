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
#elif defined(__GNUC__)
# pragma GCC diagnostic pop
#endif
	printf("%d\n", i);
	return 0;
}
