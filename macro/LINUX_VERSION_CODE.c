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
#ifdef LINUX_VERSION_MAJOR
	printf("%s: LINUX_VERSION_MAJOR = %d.\n", pfx, LINUX_VERSION_MAJOR);
	printf("%s: LINUX_VERSION_PATCHLEVEL = %d.\n", pfx, LINUX_VERSION_PATCHLEVEL);
	printf("%s: LINUX_VERSION_SUBLEVEL = %d.\n", pfx, LINUX_VERSION_SUBLEVEL);
#endif
#if LINUX_VERSION_CODE >= KERNEL_VERSION(6, 1, 0)
	printf("%s >= 6.1.0\n", pfx);
#else
	printf("%s < 6.1.0\n", pfx);
#endif

/* from kernel.mk */
#ifdef KVERSION
	printf("%s: KVERSION = %d.\n", pfx, KVERSION);
#endif
#ifdef KPATCHLEVEL
	printf("%s: KPATCHLEVEL = %d.\n", pfx, KPATCHLEVEL);
#endif
#ifdef KSUBLEVEL
	printf("%s: KSUBLEVEL = %d.\n", pfx, KSUBLEVEL);
#endif

	return 0;
}
