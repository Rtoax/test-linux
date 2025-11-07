#include <stdio.h>

void test_isoc(void)
{
#if __GLIBC_USE(ISOC89)
	printf("ISOC89\n");
#endif
#if __GLIBC_USE(ISOC11)
	printf("ISOC11\n");
#endif
#if __GLIBC_USE(ISOC2X)
	printf("ISOC2X\n");
#endif
#if __GLIBC_USE(ISOC23)
	printf("ISOC23\n");
#endif
/* see /usr/include/bits/mathcalls.h */
#if __GLIBC_USE(IEC_60559_FUNCS_EXT_C23)
	printf("IEC_60559_FUNCS_EXT_C23\n");
#endif
}

void test_deprecated(void)
{
/* -std=c89|c90 */
#if __GLIBC_USE(DEPRECATED_GETS)
	printf("gets() is available (deprecated)\n");
#endif
}

int main(void)
{
	test_isoc();
	test_deprecated();
	return 0;
}
