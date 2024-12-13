#include <stdio.h>
#include <sys/utsname.h>
#include <unistd.h>
#include <linux/version.h>

int main(void)
{
	struct utsname name;
	const char *pfx = "linux";

	uname(&name);

	pfx = name.release;

	printf("%s: LINUX_VERSION_CODE = %d.\n", pfx, LINUX_VERSION_CODE);
	printf("%s: LINUX_VERSION_MAJOR = %d.\n", pfx, LINUX_VERSION_MAJOR);
	printf("%s: LINUX_VERSION_PATCHLEVEL = %d.\n", pfx, LINUX_VERSION_PATCHLEVEL);
	printf("%s: LINUX_VERSION_SUBLEVEL = %d.\n", pfx, LINUX_VERSION_SUBLEVEL);

	return 0;
}
