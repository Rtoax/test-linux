/**
 * Many functions have no effects except to return a value, and their return
 * value depends only on the parameters and global variables. Functions of
 * this kind can be subject to data flow analysis and might be eliminated.
 */

#include <stdio.h>

#if __GNUC_PREREQ(2, 96)
/*
 * gcc: https://gcc.gnu.org/onlinedocs/gcc/Common-Function-Attributes.html#index-pure-function-attribute
 */
# define __pure __attribute__((__pure__))
/**
 * The __attribute__((pure)) and __attribute__((__pure__)) attributes in GCC
 * are actually the same. The difference in notation is just a matter of style
 * and does not affect the functionality.
 */
# define __pure2 __attribute__((pure))
#else
# define __pure
# define __pure2
#endif

int __pure func1(void)
{
	return printf("func1 pure test.\n");
}

int __pure2 func2(void)
{
	return printf("func2 pure test.\n");
}

int main(void)
{
	int a = func1();

	/* no need to return value, optimize out */
	func1();
	func1();
	func2();

	return 0;
}
