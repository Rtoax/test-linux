#include <sched.h>
#include <linux/sched.h>
#include <stdio.h>
#include <unistd.h>

const char *policy_string(int policy)
{
	switch (policy) {
#define CASE(P)	case P: return #P; break
		CASE(SCHED_NORMAL);
		CASE(SCHED_FIFO);
		CASE(SCHED_RR);
		CASE(SCHED_BATCH);
		CASE(SCHED_ISO);
		CASE(SCHED_IDLE);
		CASE(SCHED_DEADLINE);
	default:
		return "Unknown";
#undef CASE
	}
}

int main(void)
{
	int ret, policy;
	pid_t pid = getpid();
	struct sched_param sp;

	policy = SCHED_FIFO;
	sp.sched_priority = 1;

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

	printf("Success: pid %d, policy %s\n", pid, policy_string(policy));

	return 0;
}
