#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <limits.h>

#include "cgroup_helpers.h"

static char **roots;
static int nroots;

static void display_proc_cgrp(const struct proc_cgroup *cgrp, void *arg)
{
	int i, err;
	long cgroupid;
	char cgroup_path[PATH_MAX] = {0};

	for (i = 0; i < nroots; i++) {
		cgroupid = cgroup_cgroupid_of_mnt_path(roots[i], cgrp->cgroup_path);
		if (cgroupid <= 0)
			continue;

		printf("cgroupv%d %ld %d:%s:%s\n", cgrp->cgroup_type, cgroupid,
			cgrp->hierarchy_id, cgrp->subsystem_list, cgrp->cgroup_path);

		err = cgroup_cgroup_path(cgroupid, cgroup_path, PATH_MAX);
		if (err == 0)
			printf("\t%s\n", cgroup_path);

#if 0
		if (strcmp(cgrp->cgroup_path, cgroup_path)) {
			fprintf(stderr, "\033[31mERROR %s != %s\033[m\n", cgrp->cgroup_path, cgroup_path);
		}
#endif
	}
}

int main(int argc, char *argv[])
{
	int i;
	pid_t pid = getpid();

	if (argc >= 2)
		pid = atoi(argv[1]);

	nroots = cgroup_get_roots(&roots);
	for (i = 0; i < nroots; i++) {
		fprintf(stderr, "root --- %s\n", roots[i]);
	}

	cgroup_proc_for_each_cgroup_entry(pid, display_proc_cgrp, NULL);

	cgroup_free_roots(roots, nroots);

	return 0;
}
