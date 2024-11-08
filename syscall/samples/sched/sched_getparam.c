/**
 * $ sudo chrt --rr 10 ./sched_setparam
 */
#include <sched.h>
#include <stdio.h>
#include <unistd.h>

int main(void)
{
	int ret, policy;
	pid_t pid;
	struct sched_param sp;

	/* Get information */
	pid = getpid();
	policy = sched_getscheduler(pid);

	/* Get current param */
	ret = sched_getparam(pid, &sp);
	if (ret) {
		perror("sched_getparam");
		return ret;
	}
	printf("get: sched_priority = %d\n", sp.sched_priority);

	/* Set param */
	sp.sched_priority = sched_get_priority_max(policy);
	printf("set: sched_priority = %d\n", sp.sched_priority);
	ret = sched_setparam(pid, &sp);
	if (ret) {
		perror("sched_setparam");
		return ret;
	}

	return 0;
}
