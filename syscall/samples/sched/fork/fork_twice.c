/**
 * fork() twice to detach the child from the original parent
 */
#ifndef _GNU_SOURCE
#define _GNU_SOURCE
#endif
#include <sched.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>

#define LOG_DEBUG() do {	\
		printf("%s:%-3d pid %d, ppid %d\n",	\
			__func__, __LINE__, getpid(), getppid());	\
	} while (0)

bool new_pidns = false;

void parse_args(int argc, char *argv[])
{
	int i;
	for (i = 0; i < argc; i++) {
		if (!strncmp(argv[i], "pidns=", 6)) {
			new_pidns = !!atoi(argv[i] + 6);
		}
	}
}

int main(int argc, char *argv[])
{
	int err;
	pid_t pid;

	fprintf(stderr, "Usage: %s [pidns=0|1]\n", argv[0]);

	parse_args(argc - 1, &argv[1]);

	if (new_pidns) {
		err = unshare(CLONE_NEWPID);
		if (err) {
			perror("unshare");
			abort();
		}
	}

	pid = fork();
	if (pid == 0) {
		LOG_DEBUG();
		if (fork()) {
			LOG_DEBUG();
			exit(0);
		}
		LOG_DEBUG();
	}

	LOG_DEBUG();
	waitpid(pid, NULL, 0);
	LOG_DEBUG();

	return 0;
}
