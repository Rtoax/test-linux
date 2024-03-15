#ifndef _GNU_SOURCE
#define _GNU_SOURCE
#endif
#include <sys/wait.h>
#include <sys/utsname.h>
#include <sched.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define errExit(msg) do { \
		perror(msg); \
		exit(EXIT_FAILURE); \
	} while (0)

#define STACK_SIZE (1024 * 1024)

/* child */
static int childFunc(void *arg)
{
	struct utsname uts;
	char *shellname;
	/* set hostname int child UTS namespace */
	if (sethostname(arg, strlen(arg)) == -1)
		errExit("sethostname");

	/* get hostname */
	if (uname(&uts) == -1)
		errExit("uname");

	printf("uts.nodename in child:  %s\n", uts.nodename);
	printf("My PID is: %d\n", getpid());
	printf("My parent PID is: %d\n", getppid());

	/* Get shell */
	shellname = getenv("SHELL");
	if (!shellname){
		shellname = (char *)"/bin/bash";
	}
	/* execute shell */
	execlp(shellname, shellname, (char *)NULL);

	return 0;
}

int main(int argc, char *argv[])
{
	char *stack;
	char *stackTop;
	pid_t pid;

	if (argc < 2) {
		fprintf(stderr, "Usage: %s <child-hostname>\n", argv[0]);
		exit(EXIT_SUCCESS);
	}

	/* child's stack */
	stack = malloc(STACK_SIZE);
	if (stack == NULL)
		errExit("malloc");

	/* Assume stack grows downward */
	stackTop = stack + STACK_SIZE;

	/* child has new UTS namespace */
	pid = clone(childFunc, stackTop, CLONE_NEWUTS | SIGCHLD, argv[1]);
	if (pid == -1)
		errExit("clone");

	if (waitpid(pid, NULL, 0) == -1)
		errExit("waitpid");

	printf("child has terminated\n");

	exit(EXIT_SUCCESS);
}

