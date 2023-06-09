#include <stdio.h>
#include <unistd.h>
#include <syscall.h>
#include <sys/syscall.h>

int main(void)
{
#define P(nr)	printf("%30s : %d\n", #nr, nr);

	P(SYS_read);
	P(SYS_write);
	P(SYS_open);
	P(__NR_open);

	return 0;
}
