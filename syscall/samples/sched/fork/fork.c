#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/prctl.h>
#include <sys/types.h>
#include <sys/wait.h>
#ifdef SYSCALL
#include <sched_helpers.h>
#include "helpers.h"
#ifdef VFORK
#define myfork() sys_vfork()
#define NAME "sys-vfork"
#else
#define myfork() sys_fork()
#define NAME "sys-fork"
#endif
#else /* SYSCALL */
#ifdef VFORK
#define myfork() vfork()
#define NAME "vfork"
#else
/* Maybe glibc wrapper this to clone(2) */
#define myfork() fork()
#define NAME "fork"
#endif
#endif

int main(int argc, char *argv[])
{
	int val = 0;
	pid_t pid;

	prctl(PR_SET_NAME, NAME "-parent", 0, 0, 0);

	pid = myfork();
	if (pid == 0) {
		prctl(PR_SET_NAME, NAME "-child", 0, 0, 0);
		val = 1;
		printf("Child %d, val %d.\n", getpid(), val);
		exit(0);
	}

	printf("Parent %d, val %d.\n", getpid(), val);
	waitpid(pid, NULL, 0);
	return 0;
}
