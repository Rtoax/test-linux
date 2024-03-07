#include <unistd.h>
#include <stdio.h>
#include <sys/wait.h>

int main(void)
{
	pid_t pid = fork();

	if (pid == 0) {
		printf("child\n");
		sleep(5);
		return 22;
	} else {
		int status = 0;

		while (!waitpid(-1, &status, WNOHANG)) {
			sleep(1);
			printf("sleep 1 sec %d\n", status);
		}

		if (WIFEXITED(status)) {
			printf("child send: %d \n", WEXITSTATUS(status));
		}
	}

	return 0;
}
