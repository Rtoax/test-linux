#include <stdio.h>
#include <unistd.h>
#include <sys/resource.h>

int nice_self(int increment)
{
	int result, old;

	old = getpriority(PRIO_PROCESS, 0);
	fprintf(stderr, "old priority %d\n", old);

	result = setpriority(PRIO_PROCESS, 0, old + increment);
	if (result != -1)
		return old + increment;
	else {
		fprintf(stderr, "setpriority %m\n");
		return -1;
	}
}

int main(void)
{
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
