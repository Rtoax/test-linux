// SPDX-License-Identifier: (LGPL-2.1 OR BSD-2-Clause)
#include <stdio.h>
#include <stdlib.h>
#include "endian.h"

#ifdef TEST_MAIN
int main(void)
{
	if (is_little_endian())
		printf("Little Endian\n");
	else if (is_big_endian())
		printf("Big Endian\n");
	return 0;
}
#endif
