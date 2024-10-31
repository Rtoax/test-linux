#include <stdio.h>
#include <stdlib.h>
#include <spawn.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>


int main(int argc ,char *argv[])
{
	int child_pid;
	int ret;
	int wait_val;

	ret = posix_spawn(&child_pid, "/bin/ls", NULL, NULL, argv, NULL);
	if (ret != 0) {
		printf("posix_spawn error.\n");
		exit(EXIT_FAILURE);
	}

	wait(&wait_val);
	printf("wait value = %d\n", wait_val);

	return 0;
}
