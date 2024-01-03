#include <stdio.h>
#include <unistd.h>
#include <syscall.h>
#include <sys/syscall.h>

int main(void)
{
#define NR_SYS(nr)	printf("%30s : %4d(%#04x)\n", #nr, nr, nr);
#include "nr.h"
#undef NR_SYS

	return 0;
}
