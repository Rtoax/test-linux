#include <stdio.h>
#include <unistd.h>
#include <syscall.h>
#include <sys/ptrace.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/reg.h>		/* For constants ORIG_RAX etc */

int main(void)
{
	pid_t child;
	long orig_rax, rip;

	child = fork();
	if (child == 0) {
		ptrace(PTRACE_TRACEME, 0, NULL, NULL);
		execl("/bin/ls", "ls", NULL);
	} else {
		wait(NULL);

		orig_rax = ptrace(PTRACE_PEEKUSER, child,
				  sizeof(unsigned long) * ORIG_RAX, NULL);
		rip = ptrace(PTRACE_PEEKUSER, child,
			     sizeof(unsigned long) * RIP, NULL);

		printf("__NR_execve = %d\n", __NR_execve);
		printf("The child made a system call %ld\n", orig_rax);
		printf("RIP %lx\n", rip);
		ptrace(PTRACE_CONT, child, NULL, NULL);
	}
	return 0;
}
