#include <stdio.h>
#include <sys/ptrace.h>
#include <syscall.h>
#include <sys/user.h>
#include <unistd.h>
#include <wait.h>
#include <signal.h>
#include <assert.h>
#include <linux/ptrace.h>

#include "ptrace_helpers.h"

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
			unsigned long o_flags = 0;

			spid[i] = pid;
			ptrace(PTRACE_ATTACH, spid[i], NULL, NULL);
			pid = waitpid(spid[i], &status, WUNTRACED);
			assert(pid == spid[i]);

			o_flags |= PTRACE_O_TRACECLONE;
			o_flags |= PTRACE_O_TRACEEXEC;
			o_flags |= PTRACE_O_TRACEEXIT;
			o_flags |= PTRACE_O_TRACEFORK;
			o_flags |= PTRACE_O_TRACEVFORK;
			o_flags |= PTRACE_O_TRACESYSGOOD;
			o_flags |= PTRACE_O_EXITKILL;

			ptrace(PTRACE_SETOPTIONS, spid[i], NULL, o_flags);

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
	int status, sig, event;
	pid_t pid;
	struct user_regs_struct regs;
	int i;
	int count = 0;

	while (TRUE) {
		pid = waitpid(-1, &status, WUNTRACED);

		event = status >> 16;
		sig = WSTOPSIG(status);

		if (WIFEXITED(status)) {
			++count;
			if (count == 2)
				break;
		} else if (WIFSTOPPED(status) && sig == (SIGTRAP | 0x80)) {
			ptrace(PTRACE_GETREGS, pid, NULL, &regs);
			printf("%d was stopped at %llu(%s)\n",
				pid, regs.orig_rax,
				find_syscall_symbol(regs.orig_rax));
		} else if (sig == SIGTRAP && event == PTRACE_EVENT_EXEC) {
			printf("Call exec.\n");
		} else if (sig == SIGTRAP &&
				(event == PTRACE_EVENT_FORK ||
				event == PTRACE_EVENT_VFORK ||
				event == PTRACE_EVENT_CLONE)) {

			struct user_regs_struct regs;
			pid_t new_pid;
			unsigned long o_flags;

			ptrace(PTRACE_GETEVENTMSG, pid, 0, &new_pid);
			ptrace(PTRACE_GETREGS, pid, NULL, &regs);

			printf("Call vfork,fork,clone, new_pid = %d.\n", new_pid);

			ptrace(PTRACE_ATTACH, new_pid, NULL, NULL);

			o_flags = 0;
			o_flags |= PTRACE_O_TRACESYSGOOD;
			o_flags |= PTRACE_O_TRACEFORK;
			o_flags |= PTRACE_O_TRACECLONE;
			o_flags |= PTRACE_O_TRACEVFORK;
			o_flags |= PTRACE_O_TRACEEXEC;

			ptrace(PTRACE_SETOPTIONS, new_pid, NULL, o_flags);

			ptrace(PTRACE_SYSCALL, new_pid, NULL, NULL);
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
