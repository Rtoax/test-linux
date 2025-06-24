#ifndef _GNU_SOURCE
#define _GNU_SOURCE
#endif
#include <stdio.h>
#include <stdlib.h>
#include <pty.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>


int open_pty_pair(int *amaster, int *aslave)
{
#if 0
	int master, slave;
	char *name;

	master = getpt();
	if (master < 0)
		return 0;
	if (grantpt(master) < 0 || unlockpt(master) < 0)
		goto close_master;
	name = ptsname(master);
	if (name == NULL)
		goto close_master;
	slave = open(name, O_RDWR);
	if (slave == -1)
		goto close_master;
	if (isastream(slave)) {
		if (ioctl(slave, I_PUSH, "ptem") < 0 ||
		    ioctl(slave, I_PUSH, "ldterm") < 0)
			goto close_slave;
	}
	*amaster = master;
	*aslave = slave;

	return 1;

close_slave:
	close(slave);
close_master:
	close(master);
	return 0;
#else
	return -ENOSYS;
#endif
}

int main(void)
{
	return 0;
}

