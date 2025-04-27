#include <sched.h>
#include <linux/sched.h>
#include <stdio.h>
#include <unistd.h>

#include "sched_helpers.h"


int main(void)
{
	int ret, policy;
	pid_t pid = getpid();
	struct sched_param sp;

	policy = SCHED_FIFO;
	sp.sched_priority = 1;

	/**
	 * sched_setscheduler(pid, policy, NULL) is Invalid argument
	 */
	ret = sched_setscheduler(pid, policy, &sp);
	if (ret) {
		perror("sched_setscheduler");
		return ret;
	}

	ret = sched_getscheduler(pid);
	if (ret != policy) {
		perror("sched_getscheduler");
		return ret;
	}

	printf("Success: pid %d, policy %s\n", pid, sched_policy_string(policy));

	return 0;
}
