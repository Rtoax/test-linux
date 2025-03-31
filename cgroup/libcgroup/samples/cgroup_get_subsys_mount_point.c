#include <libcgroup.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ARRAY_SIZE(a) (sizeof(a) / sizeof(a[0]))


int main(int argc, char **argv)
{
	int i, ret;
	char *mntpoint;
	char *subsys[] = {
		"cpu",
		/* mount -t cgroup -ocpuacct none /sys/fs/cgroup */
		"cpuacct",
		"cpuset",
		"memory",
		"blkio",
		"devices",
		"freezer",
		"net_cls",
		"net_prio",
		"pids",
		"hugetlb",
		"perf_event",
	};

	ret = cgroup_init();
	if (ret) {
		fprintf(stderr, "cgroup_init failed\n");
		exit(1);
	}

	for (i = 0; i < ARRAY_SIZE(subsys); i++) {
		ret = cgroup_get_subsys_mount_point(subsys[i], &mntpoint);
		if (ret) {
			printf("%s : Not found\n", subsys[i]);
			continue;
		}
		printf("%s : %s\n", subsys[i], mntpoint);
		free(mntpoint);
	}

	return 0;
}
