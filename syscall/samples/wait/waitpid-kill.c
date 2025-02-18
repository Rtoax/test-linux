#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/wait.h>


int main(int argc, char *argv[])
{
	pid_t cpid, w;
	int status;

	cpid = fork();
	if (cpid == -1) {
		perror("fork");
		exit(EXIT_FAILURE);
	}

	/* child */
	if (cpid == 0) {
		printf("Child PID is %ld\n", (long) getpid());
		/* Wait for signals */
		if (argc == 1)
			pause();
		_exit(atoi(argv[1]));
	}

	/* parent */
	printf("kill [-STOP|-CONT|-TERM] %d\n", cpid);
	do {
		w = waitpid(cpid, &status, WUNTRACED | WCONTINUED);
		if (w == -1) {
			perror("waitpid");
			exit(EXIT_FAILURE);
		}

		if (WIFEXITED(status)) {
			printf("exited, status=%d\n", WEXITSTATUS(status));
		} else if (WIFSIGNALED(status)) {
			printf("killed by signal %d\n", WTERMSIG(status));
		} else if (WIFSTOPPED(status)) {
			printf("stopped by signal %d\n", WSTOPSIG(status));
		} else if (WIFCONTINUED(status)) {
			printf("continued\n");
		}
	} while (!WIFEXITED(status) && !WIFSIGNALED(status));
	exit(EXIT_SUCCESS);
	return 0;
}
