// SPDX-License-Identifier: (LGPL-2.1 OR BSD-2-Clause)
#include <stdio.h>
#include "ipaddr.h"

#if defined(TEST_MAIN)
int main(void)
{
	int i = __S2I("12113");
	printf("%d\n", i);
	printf("%x\n", IPv4S("1", "1", "1", "1"));
	return 0;
}
#endif
