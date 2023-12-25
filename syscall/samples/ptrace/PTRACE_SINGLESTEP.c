#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <sys/reg.h>
#include <sys/user.h>
#include <sys/syscall.h>
#include <sys/ptrace.h>

#include "helpers.h"


int main(void)
{
	pid_t child;
	int status;
	size_t instruction_count = 0;

	child = fork();
	if (child == 0) {
		ptrace(PTRACE_TRACEME, 0, NULL, NULL);
		execl("/bin/ls", "ls", NULL);
	}

	/* Parent process */
	while (1) {
		wait(&status);
		if (WIFEXITED(status))
			break;
		instruction_count++;
		ptrace(PTRACE_SINGLESTEP, child, NULL, NULL);
	}

	printf("instruction count %ld\n", instruction_count);
	return 0;
}

