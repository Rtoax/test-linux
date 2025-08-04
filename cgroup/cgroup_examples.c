#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "cgroup_helpers.h"


void display_proc_cgrp(const struct proc_cgroup *cgrp)
{
	printf("cgroupv%d %d:%s:%s\n", cgrp->cgroup_type, cgrp->hierarchy_id,
		cgrp->subsystem_list, cgrp->cgroup_path);
}

int main(int argc, char *argv[])
{
	long cgroupid;
	pid_t pid = getpid();

	if (argc >= 2)
		pid = atoi(argv[1]);

	cgroupid = cgroup_proc_cgroupid(pid);
	printf("PID %d CGROUP %ld\n", pid, cgroupid);

	cgroup_proc_for_each_cgroup_entry(pid, display_proc_cgrp);

	return 0;
}
