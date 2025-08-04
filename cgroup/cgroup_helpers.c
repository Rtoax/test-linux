// SPDX-License-Identifier: (LGPL-2.1 OR BSD-2-Clause)
/* Copyright (c) 2025 Rong Tao */
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <errno.h>
#include "cgroup_helpers.h"


long proc_cgroupid(pid_t pid)
{
	int err;
	char proc[64];
	struct stat st;

	snprintf(proc, sizeof(proc) - 1, "/proc/%d/cgroup", pid);
	err = stat(proc, &st);

	return err ? -errno : st.st_ino;
}
