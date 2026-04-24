#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/prctl.h>
#include <sys/types.h>
#include <sys/wait.h>
#ifdef SYSCALL
#include <sched_helpers.h>
#include "helpers.h"
#ifdef VFORK
#define myfork() sys_vfork()
#define NAME "sys-vfork"
#else
#define myfork() sys_fork()
#define NAME "sys-fork"
#endif
#else /* SYSCALL */
#ifdef VFORK
#define myfork() vfork()
#define NAME "vfork"
#else
/* Maybe glibc wrapper this to clone(2) */
#define myfork() fork()
#define NAME "fork"
#endif
#endif

void set_pname(const char *name, int n)
{
	char buf[64];
	snprintf(buf, sizeof(buf) - 1, "%s/%d", name, n);
	prctl(PR_SET_NAME, buf, 0, 0, 0);
}

void __loop_fork(int cnt, int nfork)
{
	pid_t pid;
	int val = 0;

	if (cnt >= nfork)
		return;

	set_pname(NAME, cnt * 2);

	pid = myfork();
	if (pid == 0) {
		set_pname(NAME, cnt * 2 + 1);
		printf("Child %d, val = %d.\n", getpid(), ++val);
		__loop_fork(++cnt, nfork);
		exit(0);
	}

	printf("Parent %d, val = %d.\n", getpid(), ++val);
	waitpid(pid, NULL, 0);
}

void loop_fork(int nfork)
{
	__loop_fork(0, nfork);
}

int main(int argc, char *argv[])
{
	loop_fork(5);
	return 0;
}
