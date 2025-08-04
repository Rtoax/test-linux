#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "cgroup_helpers.h"


static void display_proc_cgrp(const struct proc_cgroup *cgrp, void *arg)
{
	long cgroupid;
	cgroupid = cgroup_cgroupid2(CGROUP_DEFAULT_MNTPOINT, cgrp->cgroup_path);

	printf("cgroupv%d %ld %d:%s:%s\n", cgrp->cgroup_type, cgroupid,
		cgrp->hierarchy_id, cgrp->subsystem_list, cgrp->cgroup_path);
}

int main(int argc, char *argv[])
{
	char **roots;
	int nroots, i;
	pid_t pid = getpid();

	if (argc >= 2)
		pid = atoi(argv[1]);

	cgroup_get_roots(&roots, &nroots);
	for (i = 0; i < nroots; i++) {
		printf("%s\n", roots[i]);
		for_each_cgroup(roots[i]);
	}
	cgroup_free_roots(roots, nroots);

	cgroup_proc_for_each_cgroup_entry(pid, display_proc_cgrp, NULL);

	return 0;
}
