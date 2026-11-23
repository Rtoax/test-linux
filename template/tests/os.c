#include <stdio.h>

#ifndef __stringify
#define __stringify_1(x...) #x
#define __stringify(x...) __stringify_1(x)
#endif

#define CONCAT(a, b) a##b
#define XCONCAT(a, b) CONCAT(a, b)

#define OS_MACRO(x) XCONCAT(__, XCONCAT(x, __))

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

#if OS_MACRO(OS_ID) != 1
#error Not defined __${OS_ID}__ or is not equal to 1
#endif

void display(void)
{
	/* see template/os.mk */
#ifdef __almalinux__
	printf("OS is AlmaLinux\n");
#elif defined(__cclinux__)
	printf("OS is CCLinux\n");
#elif defined(__centos__)
	printf("OS is CentOS\n");
#elif defined(__debian__)
	printf("OS is Debian\n");
#elif defined(__fedora__)
	printf("OS is Fedora\n");
#elif defined(__kylin__)
	printf("OS is Kylin\n");
#elif defined(__ubuntu__)
	printf("OS is Ubuntu\n");
#elif defined(__opencloudos__)
	printf("OS is OpenCloudOS\n");
#elif defined(__openEuler__)
	printf("OS is openEuler\n");
#elif defined(__opensuse_leap__)
	printf("OS is openSUSE Leap\n");
#elif defined(__tencentos__)
	printf("OS is TencentOS\n");
#elif defined(__alpine__)
	printf("OS is Alpine\n");
#else
#error Must define __${distro}__, see template/os.mk
#endif
}

int main(void)
{
	printf("%s %d.%d\n", __stringify(OS_ID), __os_major__, __os_minor__);
	display();
	printf("%s\n", __stringify(OS_VERSION_ID));
	printf("%s\n", __stringify(OS_MACRO(OS_ID)));
	return 0;
}
