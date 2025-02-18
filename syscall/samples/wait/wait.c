#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>


int main(void)
{
	int status = 0;
	pid_t pid;

	pid = fork();
	if (pid == 0)
		exit(3);

	printf("son pid: %d \n", pid);

	pid = fork();
	if (pid == 0)
		exit(7);

	printf("grand-son pid: %d \n", pid);

	wait(&status);

	if (WIFEXITED(status)) {
		printf("child send1: %d \n", WEXITSTATUS(status));
	}

	wait(&status);

	if (WIFEXITED(status)) {
		printf("child send2: %d \n", WEXITSTATUS(status));
	}

	sleep(2);

	return 0;
}
