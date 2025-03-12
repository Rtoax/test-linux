#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(int argc, char *argv[])
{
	int val = 0;
	pid_t pid;

#ifdef VFORK
	pid = vfork();
#else
	pid = fork();
#endif
	if (pid == 0) {
		val = 1;
		printf("Child %d, val %d.\n", getpid(), val);
		exit(0);
	}

	printf("Parent %d, val %d.\n", getpid(), val);
	waitpid(pid, NULL, 0);
	return 0;
}
