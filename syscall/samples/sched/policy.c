#include <sched.h>
#include <linux/sched.h>
#include <stdio.h>
#include <unistd.h>

#include "sched_helpers.h"

int main(void)
{
#define CASE(P)	printf("%-32s %d\n", #P, P);
# include "sched_policy.h"
#undef CASE
	return 0;
}
