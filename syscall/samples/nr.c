#include <stdio.h>
#include <unistd.h>
#include <syscall.h>
#include <sys/syscall.h>

#include "nr2s.h"

int main(void)
{
#define NR_SYS(nr)	printf("%30s : %4d(%#04x) %s\n", #nr, nr, nr, syscall_str[nr].name);
#include "nr.h"
#undef NR_SYS

	return 0;
}
