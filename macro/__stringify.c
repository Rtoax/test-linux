#include <stdio.h>
#include <stdbool.h>

#define __stringify_1(x...)	#x
#define __stringify(x...)	__stringify_1(x)

/* #include "stdint.h" */
#include __stringify(stdint.h)
#include __stringify(STDBOOL_HDR)

#ifndef _STDINT_H
# error include stdint.h failed
#endif

/**
 * /usr/lib/gcc/x86_64-linux-gnu/14/include/stdbool.h define _STDBOOL_H
 * /usr/lib/clang/19/include/stdbool.h define __STDBOOL_H
 */
#if !defined(_STDBOOL_H) && !defined(__STDBOOL_H)
# error include stdbool.h failed
#endif

#define NUM	3

int main(void)
{
	printf("NUM = %s\n", __stringify(NUM));
	return 0;
}

