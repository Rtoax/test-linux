#include <unistd.h>
#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

#define info() printf("sid %-8d, pid %-8d, gid %-8d\n", \
		      getsid(getpid()), getpid(), getgid());

pid_t tl_setsid(void)
{
	pid_t sid = setsid();
	if (sid == -1) {
		perror("setsid");
		return -1;
	}
	return sid;
}

int main(void)
{
	pid_t sid;

	info();

	/**
	 * EPERM: The process group ID of any process equals the PID of the
	 * calling process.
	 */
	sid = tl_setsid();
	printf("sid %-8d\n", sid);

	info();

	if (fork() != 0)
		exit(0);

	info();

	sid = tl_setsid();
	printf("sid %-8d\n", sid);

	info();

	return 0;
}
