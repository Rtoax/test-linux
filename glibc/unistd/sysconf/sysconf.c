#include <stdio.h>
#include <unistd.h>


int main(void)
{
#define SYSCONF(c) printf("%-48s %-8d %-8ld\n", #c, c, sysconf(c));
#include "confs_def.h"
#undef SYSCONF
	return 0;
}
