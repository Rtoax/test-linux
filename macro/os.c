#include <stdio.h>
#include "__stringify.h"

int main(void)
{
	/* see os.mk */
	printf("ID=%s\n", __stringify(OS_ID));
#ifdef OS_FEDORA
	printf("OS is Fedora\n");
#elif defined(OS_UBUNTU)
	printf("OS is Ubuntu\n");
#else
#error Must define OS_$distro
#endif
	printf("VERSION_ID=%s\n", __stringify(OS_VERSION_ID));
	return 0;
}
