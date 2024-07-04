#include <stdio.h>
#include <stdint.h>
#include <unistd.h>
#include <syscall.h>
#include <sys/ptrace.h>
#include <sys/types.h>
#include <sys/wait.h>
#if defined(__x86_64__)
#include <sys/reg.h>		/* For constants ORIG_RAX etc */
#endif

int main(void)
{
	pid_t child;

	child = fork();
	if (child == 0) {
		ptrace(PTRACE_TRACEME, 0, NULL, NULL);
		execl("/bin/ls", "ls", NULL);
	} else {
		wait(NULL);

#if defined(__x86_64__)
		long orig_rax, rip;

		orig_rax = ptrace(PTRACE_PEEKUSER, child,
				  sizeof(unsigned long) * ORIG_RAX, NULL);
		rip = ptrace(PTRACE_PEEKUSER, child,
			     sizeof(unsigned long) * RIP, NULL);

		printf("__NR_execve = %d\n", __NR_execve);
		printf("The child made a system call %ld\n", orig_rax);
		printf("RIP %lx\n", rip);
#elif defined(__aarch64__)
# pragma message("FIXME: aarch64 don't have PTRACE_PEEKUSER?????????")
		ptrace(PTRACE_PEEKUSER, child, 0, NULL);
		perror("ptrace");
#endif

		ptrace(PTRACE_CONT, child, NULL, NULL);
	}
	return 0;
}
