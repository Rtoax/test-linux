#include <unistd.h>
#include <errno.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/syscall.h>
#include <linux/sysctl.h>

#define OSNAMESZ 128

#if 0
int sysctl(int *names, int nlen, void *oldval, size_t *oldlenp, void *newval,
	   size_t newlen)
{
	return syscall(__NR__sysctl, names, nlen, oldval, oldlenp, newval, newlen);
}
#endif
int sysctl(struct __sysctl_args *args)
{
#ifdef __NR__sysctl
	return syscall(__NR__sysctl, args);
#else
	return -ENOSYS;
#endif
}

int main(void)
{
	struct __sysctl_args args;
	char osname[OSNAMESZ];
	size_t osnamelth;
	int name[] = {CTL_KERN, KERN_OSTYPE};

	memset(&args, 0, sizeof(struct __sysctl_args));
	args.name = name;
	args.nlen = sizeof(name) / sizeof(name[0]);
	args.oldval = osname;
	args.oldlenp = &osnamelth;

	osnamelth = sizeof(osname);

	if (sysctl(&args) == -1) {
		perror("_sysctl");
		exit(EXIT_FAILURE);
	}
	printf("This machine is running %*s\n", (int)osnamelth, osname);
	exit(EXIT_SUCCESS);
	return 0;
}

