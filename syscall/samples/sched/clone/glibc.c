#include <stdio.h>
#include <sched.h>

/**
 * glibc wrapper:
 * int clone(int (*fn)(void *), void *child_stack, int flags, void *arg, ...
 *           pid_t *ptid, struct user_desc *tls, pid_t *ctid);
 *
 * syscall:
 * long clone(unsigned long flags, void *child_stack, void *ptid, void *ctid,
 *            struct pt_regs *regs);
 */

int main(void)
{
       return 0;
}
