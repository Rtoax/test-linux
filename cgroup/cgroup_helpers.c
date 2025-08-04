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
		char *s_hid = line;
		char *s_subsys = strchr(line, ':');
		char *s_path = strrchr(line, ':');

		s_subsys[0] = '\0';
		s_subsys++;
		s_path[0] = '\0';
		s_path++;

		memset(&cgrp, 0, sizeof(struct proc_cgroup));

		cgrp.hierarchy_id = atoi(s_hid);

		if (strlen(s_subsys) == 0) {
			cgrp.cgroup_type = 2;	/* cgroupv2 */
		} else {
			cgrp.cgroup_type = 1;	/* cgroupv1 */
			sprintf(cgrp.subsystem_list, s_subsys);
		}
		/* strlen() to strip '\n' */
		snprintf(cgrp.cgroup_path, strlen(s_path), s_path);

		lines++;
		callback(&cgrp);
	}

	fclose(f);
	return lines;
}
