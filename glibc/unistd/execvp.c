#include <unistd.h>
#include <stdio.h>
#include <sys/wait.h>

#include "unistd_helpers.h"

#define ARRAY_SIZE(arr) (sizeof(arr) / sizeof(arr[0]))

int main(int argc, char *argv[])
{
	int i;
	pid_t pid;

	char *_argv1[] = { "ls", "-a", NULL };
	char *_argv2[] = { "-a", "-l", NULL };
	char *_argv3[] = { "-a", NULL };

	char *(*argvs[]) = {
		_argv1,
		_argv2,
		_argv3,
	};

	display_argv(argc, argv, ',', '\n');

	for (i = 0; i < ARRAY_SIZE(argvs); i++) {
		pid = fork();
		if (pid == 0)
			execvp("ls", argvs[i]);
		wait(NULL);
	}

	return 0;
}
