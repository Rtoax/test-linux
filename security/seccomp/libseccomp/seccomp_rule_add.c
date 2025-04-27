/**
 * File: seccomp_rule_add.c
 *
 * Ref:
 * https://www.anquanke.com/post/id/208364
 */

#include <unistd.h>
#include <seccomp.h>
#include <linux/seccomp.h>


int main(void)
{
	char *str = "/bin/sh";
	scmp_filter_ctx ctx;

	ctx = seccomp_init(SCMP_ACT_ALLOW);
	seccomp_rule_add(ctx, SCMP_ACT_KILL, SCMP_SYS(execve), 0);
	seccomp_load(ctx);
	write(1, "hello world\n", 12);

	/* Killed: SCMP_ACT_KILL */
	syscall(__NR_execve, str, NULL, NULL);

	seccomp_release(ctx);
	return 0;
}
