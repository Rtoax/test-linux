#include <sys/types.h>
#include <signal.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/ptrace.h>
#include <sys/reg.h>
#include <sys/user.h>

#include "breakfast.h"

static int global_a = 0;

int fact(int n)
{
	global_a += 1;
	if (n <= 1)
		return 1;
	return n * fact(n-1);
}

void child(void)
{
	kill(getpid(), SIGSTOP);
	printf("fact(5) = %d\n", fact(10));
}

void parent(pid_t pid)
{
	struct breakpoint *fact_break, *last_break = NULL;
	void *fact_ip = &fact, *last_ip;
	breakfast_attach(pid);
	fact_break = breakfast_break(pid, fact_ip);
	while (breakfast_run(pid, last_break)) {
		last_ip = breakfast_getip(pid);
		if (last_ip == fact_ip) {
#if defined(__x86_64)
			int arg = ptrace(PTRACE_PEEKUSER, pid, sizeof(long)*RDI);
#else
			struct user_regs_struct s;
			ptrace(PTRACE_GETREGS, pid, 0, &s);
			int arg = ptrace(PTRACE_PEEKDATA, pid, sizeof(long) + s.esp);
#endif
			printf("Break at fact(%d)\n", arg);
			last_break = fact_break;
		} else {
			printf("Unknown trap at %p\n", last_ip);
			last_break = NULL;
		}
	}
}

int main(void)
{
	pid_t pid;
	if ((pid = fork()) == 0)
		child();
	else
		parent(pid);
	return 0;
}

