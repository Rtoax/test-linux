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
#include <fcntl.h>
#include <sched.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

#include "helpers.h"


void print_pidns(void)
{
	char buf[128];
	readlink("/proc/self/ns/pid", buf, sizeof(buf));
	printf("PID %-8d PIDNS %s\n", getpid(), buf);
}

int main(int argc, char *argv[])
{
	int err;
	pid_t parent, pid_1, pid_2;

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
			try_fork();
			printf("PID %d sleeping...\n", getpid());
			sleep(1);
			printf("PID %d calling fork(2).\n", getpid());
			try_fork();
			sleep(1);
			try_fork();
			try_fork();
			exit(0);
		}

		/* PID1 running from here */

		print_pidns();
		printf("PID %d sleeping...\n", getpid());
		sleep(1);
		printf("PID %d exit.\n", getpid());
		exit(0);
	}
	printf("PARENT sleeping 2 s\n");
	sleep(3);

	if (pid_1 > 0) {
		printf("PARENT waiting PID1\n");
		waitpid(pid_1, NULL, 0);
	}
	printf("PARENT finish.\n");

	return 0;
}
