#include <stdio.h>
#include <unistd.h>

#include "cgroup_helpers.h"


int main(void)
{
	unsigned long cgroupid;
	const pid_t pid = getpid();

	cgroupid = proc_cgroupid(pid);
	printf("PID %d CGROUP %ld\n", pid, cgroupid);

	return 0;
}
