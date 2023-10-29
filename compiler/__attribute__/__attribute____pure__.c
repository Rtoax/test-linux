#include <stdio.h>

#if __GNUC_PREREQ(2, 96)
# define __pure __attribute__((__pure__))
#else
# define __pure
#endif

int __pure func1(void)
{
	return printf("func1 pure test.\n");
}

int main(void)
{
	int a = func1();

	/* no need to return value, optimize out */
	func1();
	func1();

	return 0;
}
