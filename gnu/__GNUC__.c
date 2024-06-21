#include <stdio.h>

#if defined(__GNUC__) && ((__GNUC__ == 4) && (__GNUC_MINOR__ >= 5) || __GNUC__ >= 5)
/* do some check */
#endif

int main(void)
{
	printf("__GNUC__ = %d.\n", __GNUC__);
	printf("__GNUC_MINOR__ = %d.\n", __GNUC_MINOR__);
	printf("__GNUC_PATCHLEVEL__ = %d.\n", __GNUC_PATCHLEVEL__);
	return 0;
}
