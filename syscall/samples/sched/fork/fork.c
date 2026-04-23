#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/prctl.h>
#include <sys/types.h>
#include <sys/wait.h>

#ifdef SYSCALL
#include "fork_helpers.h"
#define fork() sys_fork()
#define vfork() sys_vfork()
#endif

int main(int argc, char *argv[])
{
	int val = 0;
	pid_t pid;

	prctl(PR_SET_NAME, "fork-parent", 0, 0, 0);

#ifdef VFORK
	pid = vfork();
#else
	pid = fork();
#endif
	if (pid == 0) {
		prctl(PR_SET_NAME, "fork-child", 0, 0, 0);
		val = 1;
		printf("Child %d, val %d.\n", getpid(), val);
		exit(0);
	}

	printf("Parent %d, val %d.\n", getpid(), val);
	waitpid(pid, NULL, 0);
	return 0;
}
