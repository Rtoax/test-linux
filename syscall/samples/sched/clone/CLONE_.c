#ifndef _GNU_SOURCE
#define _GNU_SOURCE
#endif
#include <stdio.h>
#include <sched.h>
#include <signal.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/mount.h>

int main(void)
{
#define DEF_CLONE(v) printf("%32s : %#016x (%d)\n", #v, v, v)
# include "CLONE_.h"
#undef DEF_CLONE
	return 0;
}
