#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

#if defined(TRY_FORK) || defined(TRY_VFORK)
void try_fork(void)
{
#ifdef TRY_VFORK
	pid_t pid = vfork();
#else
	pid_t pid = fork();
#endif
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
