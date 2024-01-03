#include <linux/futex.h>
#include <sys/time.h>
#include <unistd.h>
#include <sys/syscall.h>

#define weak_alias(name, aliasname) \
	extern typeof (name) aliasname __attribute__ ((weak, alias(#name)))

static long sys_futex(void *addr1, int op, int val1, struct timespec *timeout,
		      void *addr2, int val3)
{
	return syscall(SYS_futex, addr1, op, val1, timeout, addr2, val3);
}

weak_alias(sys_futex, futex);
