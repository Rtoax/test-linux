struct syscall_n_str {
	int num;
	char *name;
} syscall_str[] = {
#define NR_SYS(nr)
#define __NR_SYS(nr)	[__NR_##nr] = { .num = __NR_##nr, .name = #nr },
#include "nr.h"
#undef __NR_SYS
#undef NR_SYS
};

