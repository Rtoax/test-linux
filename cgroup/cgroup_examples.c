#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <limits.h>

#include "cgroup_helpers.h"


static void display_proc_cgrp(const struct proc_cgroup *cgrp, void *arg)
{
	long cgroupid;
	char cgroup_path[PATH_MAX] = {0};

	cgroupid = cgroup_cgroupid_of_mnt_path(CGROUP_DEFAULT_MNTPOINT, cgrp->cgroup_path);

	cgroup_cgroup_path(cgroupid, cgroup_path, PATH_MAX);

	printf("cgroupv%d %ld %d:%s:%s %s\n", cgrp->cgroup_type, cgroupid,
		cgrp->hierarchy_id, cgrp->subsystem_list, cgrp->cgroup_path, cgroup_path);
}

int main(int argc, char *argv[])
{
	pid_t pid = getpid();

	if (argc >= 2)
		pid = atoi(argv[1]);

	cgroup_proc_for_each_cgroup_entry(pid, display_proc_cgrp, NULL);

	return 0;
}
