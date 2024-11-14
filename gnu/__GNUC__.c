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

	/* This macro expands to a string constant which describes the version
	 * of the compiler in use. You should not rely on its contents having
	 * any particular form, but it can be counted on to contain at least
	 * the release number. */
	printf("%s: __VERSION__ = %s\n", pfx, __VERSION__);
	return 0;
}
