// SPDX-License-Identifier: (LGPL-2.1 OR BSD-2-Clause)
/* Copyright (c) 2025 Rong Tao */
#pragma once
#include <unistd.h>
#include <sys/types.h>

#define CGROUP_DEFAULT_MNTPOINT	"/sys/fs/cgroup/"

/* /proc/PID/cgroup content */
struct proc_cgroup {
	/* 1 or 2 */
	int cgroup_type;
	int hierarchy_id;
	char subsystem_list[128];
	char cgroup_path[1024];
};

/**
 * Get cgroup mountpoints.
 *
 * @roots need to be free with cgroup_free_roots(), access with roots[idx].
 *
 * On success, the number of root path returned, need pass to cgroup_free_roots()
 * nentries parameter. On error, -errno returned.
 */
int cgroup_get_roots(char ***roots);
int cgroup_free_roots(char **roots, int nentries);

/**
 * Get cgroup id from cgroup path.
 *
 * On success, the cgroupid returned. On error, -errno returned.
 */
long cgroup_cgroupid_of_path(const char *cgroup_path);
long cgroup_cgroupid_of_mnt_path(const char *mntpoint, const char *cgroup_path);

/**
 * Get cgroup path from cgroupid.
 *
 * On success, zero returned. On error, -errno returned.
 */
int cgroup_cgroup_path(long cgroupid, char *buf, size_t buf_len);

int cgroup_proc_for_each_cgroup_entry(pid_t pid, void (*callback)(const struct proc_cgroup *cgrp,
								  void *arg),
				      void *arg);
