#include <stdio.h>
#include "__stringify.h"

void display(void)
{
	/* see os.mk */
	printf("ID=%s\n", __stringify(OS_ID));
#ifdef __fedora__
	printf("OS is Fedora\n");
#elif defined(__ubuntu__)
	printf("OS is Ubuntu\n");
#elif defined(__debian__)
	printf("OS is Debian\n");
#elif defined(__cclinux__)
	printf("OS is CCLinux\n");
#elif defined(__centos__)
	printf("OS is CentOS\n");
#else
#error Must define OS_$distro
#endif
	printf("VERSION_ID=%s\n", __stringify(OS_VERSION_ID));
}

int main(void)
{
	display();
	return 0;
}
