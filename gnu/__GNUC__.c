#include <stdio.h>

#if defined(__GNUC__) && ((__GNUC__ == 4) && (__GNUC_MINOR__ >= 5) || __GNUC__ >= 5)
/* do some check */
#endif

int main(void)
{
	const char *pfx = "GCC";
#ifdef __clang__
	pfx = "clang";
#endif
	printf("%s: __GNUC__ = %d.\n", pfx, __GNUC__);
	printf("%s: __GNUC_MINOR__ = %d.\n", pfx, __GNUC_MINOR__);
	printf("%s: __GNUC_PATCHLEVEL__ = %d.\n", pfx, __GNUC_PATCHLEVEL__);
	return 0;
}
