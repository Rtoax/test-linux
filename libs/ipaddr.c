#include <stdio.h>
#include "ipaddr.h"

#if defined(TEST)
int main(void)
{
	int i = __S2I("12113");
	printf("%d\n", i);
	printf("%x\n", IPv4S("1", "1", "1", "1"));
	return 0;
}
#endif
