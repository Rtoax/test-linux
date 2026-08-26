/*
 * Add the pseudo keyword 'fallthrough' so case statement blocks
 * must end with any of these keywords:
 *   break;
 *   fallthrough;
 *   continue;
 *   goto <label>;
 *   return [expression];
 *
 * gcc: https://gcc.gnu.org/onlinedocs/gcc/Statement-Attributes.html#Statement-Attributes
 *
 * see also linux: include/linux/compiler_attributes.h
 */
#include <stdio.h>

#if __has_attribute(__fallthrough__)
#define fallthrough __attribute__((__fallthrough__))
#else
#define fallthrough do {} while (0)  /* fallthrough */
#endif

int main(int argc, char *argv[])
{
	switch (argc) {
	case 0:
		fallthrough;
	case 1:
		break;
	case 2:
		fallthrough;
	default:
		break;
	}
	return 0;
}
