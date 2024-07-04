#include <stdio.h>
#include <sys/ptrace.h>
#include <syscall.h>
#include <sys/user.h>
#include <unistd.h>
#include <wait.h>
#include <signal.h>
#include <assert.h>
#include <linux/ptrace.h>

#include "helpers.h"

#define TRUE	1
#define FALSE   0
#define VAR_NUM 1

pid_t spid[VAR_NUM];

static void ptrace1_setup(char **argv)
{
	pid_t pid;
	int status;
	int i;

	for (i = 0; i < VAR_NUM; ++i) {
		pid = fork();
		if (pid < 0) {
			perror("fork");
		/* child */
		} else if (pid == 0) {
			execv(argv[1], argv + 1);
		/* parent */
		} else {
			spid[i] = pid;
			ptrace(PTRACE_ATTACH, spid[i], NULL, NULL);
			pid = waitpid(spid[i], &status, WUNTRACED);
			assert(pid == spid[i]);

			ptrace(PTRACE_SETOPTIONS, spid[i], NULL,
				PTRACE_O_TRACEEXEC | PTRACE_O_TRACEEXIT |
				PTRACE_O_TRACESYSGOOD | PTRACE_O_EXITKILL);

			ptrace(PTRACE_SYSCALL, spid[i], NULL, NULL);

			waitpid(spid[i], &status, WUNTRACED);
		}
	}

	for (i = 0; i < VAR_NUM; ++i) {
		/* Continue and stop at the next (return from) syscall. */
		ptrace(PTRACE_SYSCALL, spid[i], NULL, NULL);
	}
}

static void wait_for_procs(void)
{
	int status, sig;
	pid_t pid;
	struct user_regs_struct regs;
	int i;
	int count = 0;

	while (TRUE) {
		pid = waitpid(-1, &status, WUNTRACED);
		sig = WSTOPSIG(status);

		if (WIFEXITED(status)) {
			++count;
			if (count == 2)
				break;
		} else if (WIFSTOPPED(status) && sig == (SIGTRAP | 0x80)) {
			ptrace(PTRACE_GETREGS, pid, NULL, &regs);
			printf("%d was stopped at %llu(%s), fork : %d, vfork : %d, clone : %d\n",
				pid, regs.orig_rax, find_syscall_symbol(regs.orig_rax),
				__NR_fork, __NR_vfork, __NR_clone);
		}

		if (count == 0) {
			for (i = 0; i < VAR_NUM; ++i) {
				ptrace(PTRACE_SYSCALL, spid[i], NULL, NULL);
			}
		}

		ptrace(PTRACE_SYSCALL, spid[0], NULL, NULL);
	}
}

int main(int argc, char *argv[])
{
	ptrace1_setup(argv);
	wait_for_procs();
	return 0;
}
