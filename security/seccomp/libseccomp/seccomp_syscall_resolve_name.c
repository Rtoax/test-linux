#include <stdio.h>
#include <unistd.h>
#include <seccomp.h>
#include <linux/seccomp.h>


int main(void)
{
	int sysno;

	sysno = seccomp_syscall_resolve_name("openat");
	printf("openat: %d\n", sysno);

	return 0;
}
