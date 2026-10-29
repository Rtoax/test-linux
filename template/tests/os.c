#include <stdio.h>

#define __stringify_1(x...) #x
#define __stringify(x...) __stringify_1(x)

#ifndef OS_ID
#error Not defined OS_ID
#endif
#ifndef OS_VERSION_ID
#error Not defined OS_VERSION_ID
#endif
#ifndef __os_major__
#error Not defined __os_major__
#endif
#ifndef __os_minor__
#error Not defined __os_minor__
#endif

int main(void)
{
	printf("%s %d.%d\n", __stringify(OS_ID), __os_major__, __os_minor__);
	printf("%s\n", __stringify(OS_VERSION_ID));
	return 0;
}
