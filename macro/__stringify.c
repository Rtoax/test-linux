#include <stdio.h>

#define __stringify_1(x...)	#x
#define __stringify(x...)	__stringify_1(x)

/* #include "stdint.h" */
#include __stringify(stdint.h)
#include __stringify(STDBOOL_HDR)

#ifndef _STDINT_H
# error include stdint.h failed
#endif

#ifndef _STDBOOL_H
# error include stdbool.h failed
#endif

#define NUM	3

int main(void)
{
	printf("NUM = %s\n", __stringify(NUM));
	return 0;
}

