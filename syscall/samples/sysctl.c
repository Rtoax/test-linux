#ifndef _GNU_SOURCE
#define _GNU_SOURCE
#endif
#include <unistd.h>
#include <sys/syscall.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <linux/sysctl.h>

/* Removed in Linux 5.5, glibc 2.32 */
int _sysctl(struct __sysctl_args *args);

#if !defined(__aarch64__)
int sysctl(struct __sysctl_args *args)
{
	if (syscall(SYS__sysctl, args) == -1) {
		perror("_sysctl");
		exit(EXIT_FAILURE);
	}
	return 0;
}
#else
# define sysctl(arg)
#endif

#define OSNAMESZ 100

int main(void)
{
	struct __sysctl_args args;
	char osname[OSNAMESZ];
	size_t osnamelth;
	int name[] = { CTL_KERN, KERN_OSTYPE };

	memset(&args, 0, sizeof(struct __sysctl_args));
	args.name = name;
	args.nlen = sizeof(name) / sizeof(name[0]);
	args.oldval = osname;
	args.oldlenp = &osnamelth;

	osnamelth = sizeof(osname);

	sysctl(&args);

	printf("This machine is running %*s\n", (int)osnamelth, osname);
	exit(EXIT_SUCCESS);
}
