/**
 * fork(2) failed with ENOMEM
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

int main(int argc, char *argv[])
{
	pid_t pid_1, pid_2;

	/**
	 * TODO: emulate fork failed with ENOMEM, see pid_namespaces(7)
	 */

	unshare(CLONE_NEWPID);

	pid_1 = fork();
	if (pid_1 == 0) {
		exit(0);
	}

	pid_2 = fork();
	if (pid_2 == 0) {
		sleep(1);
		try_fork();
	}

	waitpid(pid_1, NULL, 0);
	waitpid(pid_2, NULL, 0);

	return 0;
}
