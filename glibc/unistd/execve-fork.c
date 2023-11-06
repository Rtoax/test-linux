#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>

extern char **environ;

int main(void)
{
	int pid;
	char *const argv [] = { "-a", NULL };
	char *const envp [] = { "ROOT=/", NULL };

	switch ((pid = vfork())) {
	case 0:
		printf("child process.\n");
		execve("/bin/date", argv, envp);
		printf("child process done.\n");
		break;

	case -1:
		printf("fork error.\n");
		break;

	default:
		printf("parent process.\n");
		waitpid(pid, NULL, 0);
		printf("parent wait done.\n");
		break;
	}

	printf("\n\n main done.\n\n");
	return 0;
}
