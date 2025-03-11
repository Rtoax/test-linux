#ifndef _GNU_SOURCE
#define _GNU_SOURCE
#endif
#include <sched.h>
#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <limits.h>
#include <sys/ioctl.h>
#include <sys/types.h>
#include <linux/nsfs.h>


int main(void)
{
	int ret, ns, uns;
	char path[PATH_MAX];

	snprintf(path, sizeof(path), "/proc/%d/ns/uts", getpid());

	ns = open(path, O_RDONLY);
	if (ns == -1) {
		perror("open");
		return 1;
	}

	uns = ioctl(ns, NS_GET_USERNS);
	if (uns == -1) {
		perror("ioctl");
		return 1;
	}
	printf("USERNS = %d\n", uns);

	ret = unshare(CLONE_NEWUSER);
	if (ret == -1) {
		perror("unshare");
		return 1;
	}

	uns = ioctl(ns, NS_GET_USERNS);
	if (uns >= 0 || errno != EPERM) {
		printf("Don't get EPERM.\n");
		return -1;
	}

	close(ns);

	return 0;
}

