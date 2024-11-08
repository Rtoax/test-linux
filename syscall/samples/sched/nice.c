#include <stdio.h>
#include <stdlib.h>
#include <sched.h>
#include <unistd.h>
#include <linux/sched.h>
#include <sys/resource.h>


int nice_self(int increment)
{
	int err, old;
	struct sched_param sp;

	/**
	 * sched_getparam() get the RT priority.
	 */
	err = sched_getparam(getpid(), &sp);
	if (sp.sched_priority != 0) {
		fprintf(stderr, "Get none zero RT priority???\n");
		abort();
	}

	old = getpriority(PRIO_PROCESS, 0);
	fprintf(stderr, "old priority %d\n", old);

	/**
	 * sched_setparam() set the RT priority.
	 */
	err = setpriority(PRIO_PROCESS, 0, old + increment);
	if (err != -1)
		return old + increment;
	else {
		fprintf(stderr, "setpriority %m\n");
		return -1;
	}
}

int main(void)
{
	int policy;
	policy = sched_getscheduler(getpid());
	if (policy != SCHED_NORMAL) {
		fprintf(stderr, "Not SCHED_NORMAL task.\n");
		return -1;
	}

	/**
	 * +19 (low priority) to -20 (high priority)
	 */
	nice(1);
	nice_self(1);
	nice_self(1);
	nice_self(1);
	nice_self(1);
	nice_self(15);
	nice_self(1);
	nice_self(1);
	nice_self(1);
	/**
	 * since Linux 2.6.12, an unprivileged process can decrease the nice
	 * value of a target process that has a suitable RLIMIT_NICE soft
	 * limit.
	 */
	nice_self(-10);
	nice_self(-10);
	nice_self(-10);
	nice_self(-10);
	nice_self(-10);
	nice_self(-10);
	return 0;
}
