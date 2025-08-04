// SPDX-License-Identifier: (LGPL-2.1 OR BSD-2-Clause)
/* Copyright (c) 2025 Rong Tao */
#pragma once
#include <unistd.h>
#include <sys/types.h>


/* /proc/PID/cgroup content */
struct proc_cgroup {
	/* 1 or 2 */
	int cgroup_type;
	int hierarchy_id;
	char subsystem_list[128];
	char cgroup_path[1024];
};

int cgroup_proc_for_each_cgroup_entry(pid_t pid,
				      void (*callback)(const struct proc_cgroup *cgrp));

long cgroup_proc_cgroupid(pid_t pid);
