#include <stdio.h>
#include <unistd.h>
#include <syscall.h>
#include <sys/syscall.h>


int main(void)
{
#define NR_SYS(nr)	printf("%30s : %d\n", #nr, nr);
#include "nr.h"
#undef NR_SYS

	return 0;
}
