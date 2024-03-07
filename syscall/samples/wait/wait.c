#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>


int main(void)
{
	pid_t pid = fork();

	if (pid == 0) {
		exit(3);
	} else {
		printf("child pid: %d \n", pid);

		pid_t pid = fork();

		if (pid == 0) {
			exit(7);
		} else {
			printf("child pid: %d \n", pid);

			int status = 0;

			wait(&status);

			if (WIFEXITED(status)) {
				printf("child send1: %d \n", WEXITSTATUS(status));
			}

			wait(&status);

			if (WIFEXITED(status)) {
				printf("child send2: %d \n", WEXITSTATUS(status));
			}

			sleep(2);
		}
	}

	return 0;
}
