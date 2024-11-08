/**
 * See also $ chrt --max
 */
#include <stdio.h>
#include <unistd.h>
#include <sched.h>
#include <linux/sched.h>


int main(void)
{
	printf("%-16s %-8s %-8s %-8s\n", "POLICY", "NUM", "MIN", "MAX");

#define RANGE(policy) do {	\
		printf("%-16s %-8d %-8d %-8d\n",	\
			#policy, policy,	\
			sched_get_priority_min(policy),	\
			sched_get_priority_max(policy));	\
	} while (0)

	RANGE(SCHED_OTHER);
	RANGE(SCHED_NORMAL);
	RANGE(SCHED_FIFO);
	RANGE(SCHED_RR);
	RANGE(SCHED_BATCH);
	RANGE(SCHED_ISO);
	RANGE(SCHED_IDLE);
	RANGE(SCHED_DEADLINE);

#undef RANGE

	return 0;
}
