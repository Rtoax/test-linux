#include <stdio.h>
#include <sys/resource.h>
#include "helpers.h"

void print_rlimit(const char *prefix, struct rlimit *rlimit)
{
	printf("%s : %ld %ld\n", prefix, rlimit->rlim_cur, rlimit->rlim_max);
}
