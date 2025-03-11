#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

#ifdef TRY_FORK
void try_fork(void)
{
	pid_t pid = fork();
	if (pid == -1) {
		perror("fork");
		return;
	}

	if (pid == 0) {
		char *argv[] = {"echo", "child", NULL};
		execvp(argv[0], argv);
	}
	wait(NULL);
}
#else
#define try_fork()
#endif

int main(int argc, char *argv[])
{
	unsigned long count = 0;
	while (1) {
		printf("Sleeping %ld s\n", count++);
		sleep(1);
		try_fork();
	}
	return 0;
}
