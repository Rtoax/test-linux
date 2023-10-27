#include <linux/seccomp.h>  /* Definition of SECCOMP_* constants */
#include <linux/filter.h>   /* Definition of struct sock_fprog */
#include <linux/audit.h>    /* Definition of AUDIT_* constants */
#include <linux/signal.h>   /* Definition of SIG* constants */
#include <sys/ptrace.h>     /* Definition of PTRACE_* constants */
#include <sys/syscall.h>    /* Definition of SYS_* constants */
#include <unistd.h>


int sys_seccomp(unsigned int operation, unsigned int flags, void *args)
{
	int ret = syscall(SYS_seccomp, operation, flags, args);
	return ret;
}
