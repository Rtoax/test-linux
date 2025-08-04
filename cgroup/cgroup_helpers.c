// SPDX-License-Identifier: (LGPL-2.1 OR BSD-2-Clause)
/* Copyright (c) 2025 Rong Tao */
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <string.h>
#include <errno.h>
#include "cgroup_helpers.h"


/* FIXME: wrong cgroupid, use /sys/fs/cgroup/FILE instead */
long cgroup_proc_cgroupid(pid_t pid)
{
	int err;
	char proc[64];
	struct stat st;

	snprintf(proc, sizeof(proc) - 1, "/proc/%d/cgroup", pid);
	err = stat(proc, &st);

	return err ? -errno : st.st_ino;
}

int cgroup_proc_for_each_cgroup_entry(pid_t pid,
				      void (*callback)(const struct proc_cgroup *cgrp))
{
	char line[512];
	char proc[64];
	FILE *f;
	int lines = 0;
	struct proc_cgroup cgrp;

	if (!callback)
		return -EINVAL;

	snprintf(proc, sizeof(proc) - 1, "/proc/%d/cgroup", pid);

	f = fopen(proc, "r");

	/**
	 * parse each line, for example:
	 * 11:memory:/user.slice/user-1000.slice/session-1.scope
	 * 1:name=systemd:/user.slice/user-1000.slice/session-1.scope
	 * 0::/user.slice/user-1000.slice/session-1.scope
	 */
	while (fgets(line, sizeof(line), f)) {
		memset(&cgrp, 0, sizeof(struct proc_cgroup));
		/* cgroupv2 is more popular */
		cgrp.cgroup_type = 2;

		/* at least has 2 item, cgroupv2 subsystem_list is empty */
		if (sscanf(line, "%d::%s", &cgrp.hierarchy_id, cgrp.cgroup_path) != 2) {
			/* If is cgroupv1 */
			if (sscanf(line, "%d:%s:%s", &cgrp.hierarchy_id,
				   cgrp.subsystem_list, cgrp.cgroup_path) != 3) {
				continue;
			}
			cgrp.cgroup_type = 1;
		}

		lines++;
		callback(&cgrp);
	}

	fclose(f);
	return lines;
}
