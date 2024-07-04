#include <stdio.h>
#include <unistd.h>
#include <syscall.h>
#include <sys/syscall.h>

struct {
	int num;
	char *name;
} syscall_str[] = {
#define NR_SYS(nr)
#define __NR_SYS(nr)	[__NR_##nr] = { .num = __NR_##nr, .name = #nr },
#include "nr.h"
#undef __NR_SYS
#undef NR_SYS
};

int main(void)
{
#define NR_SYS(nr)	printf("%30s : %4d(%#04x) %s\n", #nr, nr, nr, syscall_str[nr].name);
#include "nr.h"
#undef NR_SYS

	return 0;
}
