#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/prctl.h>

int main(void)
{
	int pid = fork();
	if (pid == 0) {
		prctl(PR_SET_NAME, "child-sleep", 0, 0, 0);
		for (;;) {
			printf("Child sleeping...\n");
			sleep(3);
		}
		exit(1);
	}

	sleep(1);

	/**
	 * If parent process crash, child process will reparent to init process.
	 */
	printf("Parent crash.\n");
	{
		char str[1];
		str[100000] = 'a';
		(void)str;
	}

	return 0;
}
