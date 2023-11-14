#ifndef _GNU_SOURCE
#define _GNU_SOURCE
#endif
#include <sched.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <sys/wait.h>
#include <unistd.h>
#include <sys/types.h>
#include <signal.h>


#define STACK_SIZE	5000

static char child_stack[STACK_SIZE];

void grchild(int num)
{
	printf("child(%d) in ns my PID: %d Parent ID=%d\n",
		num, getpid(), getppid());
	sleep(5);
	puts("end child");
}

int child_fn(void *arg)
{
	int i;
	int ppid = (intptr_t)arg;
	printf("PID: %ld, Parent: %d\n", (long)getpid(), getppid());
	printf("ppid	= %d\n", ppid);
	for (i = 0; i < 3; i++) {
		if (fork() == 0) {
			grchild(i + 1);
			exit(0);
		}
		/* no effect  */
		kill(ppid, SIGKILL);
	}
	sleep(1);
	kill(2, SIGKILL);
	sleep(3);
	return 0;
}

int main(void)
{
	int ret;
	pid_t ppid = getpid();
	pid_t pid = clone(child_fn, child_stack + STACK_SIZE, CLONE_NEWPID, (void *)ppid);
	if (pid == -1) {
		perror("clone");
		return -1;
	}
	printf("clone() = %d\n", pid);

	ret = waitpid(pid, NULL, 0);
	if (ret) {
		perror("waitpid");
		return 0;
	}
	return 0;
}

