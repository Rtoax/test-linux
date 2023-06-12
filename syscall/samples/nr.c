#include <stdio.h>
#include <unistd.h>
#include <syscall.h>
#include <sys/syscall.h>

int main(void)
{
#define P(nr)	printf("%30s : %d\n", #nr, nr);

	P(SYS_read);
	P(SYS_write);
#if !defined(__aarch64__)
	P(SYS_open);
	P(__NR_open);
#endif
	P(SYS_openat);
	P(SYS_openat2);

	return 0;
}
