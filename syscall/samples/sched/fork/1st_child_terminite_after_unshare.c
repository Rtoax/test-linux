/**
 * fork(2) failed with ENOMEM
 *
 * Another possible scenario can occur after a call to unshare(2): if the first
 * child subsequently created by a fork(2) terminates, then subsequent calls to
 * fork(2) fail with ENOMEM. see pid_namespaces(7).
 */
#ifndef _GNU_SOURCE
#define _GNU_SOURCE
#endif
#include <assert.h>
#include <fcntl.h>
#include <sched.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

#include "helpers.h"

#define LOG(fmt...) do {	\
		printf("%16s():%-3d pid %-8d, ppid %-8d: ",	\
			__func__, __LINE__, getpid(), getppid());	\
		printf(fmt);	\
		fflush(stdout);	\
	} while (0)

void print_pidns(void)
{
	char buf[128] = {0};
	readlink("/proc/self/ns/pid", buf, sizeof(buf));
	LOG("PIDNS %s\n", buf);
}

int main(int argc, char *argv[])
{
	int err;
	pid_t parent, pid_1, pid_2;
	int secs = 1;

	/**
	 * TODO: emulate fork failed with ENOMEM, see pid_namespaces(7)
	 */

	parent = getpid();
	(void)parent;

	print_pidns();
	err = unshare(CLONE_NEWPID);
	if (err) {
		perror("unshare");
		abort();
	}
	print_pidns();

	pid_1 = fork();
	if (pid_1 == 0) {
		pid_2 = fork();
		if (pid_2 == 0) {
			daemon(1, 1);

			print_pidns();
			LOG("sleeping...\n");
			sleep(secs * 2);
			LOG("calling fork(2).\n");
			try_fork();
			try_fork();
			try_fork();
			exit(0);
		}

		/* PID1 running from here */

		print_pidns();
		LOG("sleeping...\n");
		sleep(secs * 1);
		LOG("exit.\n");
		//*(int *)0 = 1;
		//assert(0);
		exit(0);
	}
	LOG("PARENT sleeping\n");
	sleep(secs * 3);

	if (pid_1 > 0) {
		LOG("PARENT waiting PID1\n");
		waitpid(pid_1, NULL, 0);
	}
	LOG("PARENT finish.\n");

	return 0;
}
