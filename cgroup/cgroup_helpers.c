// SPDX-License-Identifier: (LGPL-2.1 OR BSD-2-Clause)
/* Copyright (c) 2025 Rong Tao */
#include <dirent.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <string.h>
#include "cgroup_helpers.h"

/**
 * Get cgroup mountpoints.
 */
int cgroup_get_roots(char ***roots, int *nentries)
{
	char line[1024];
	char fsname[128];
	char mountpoint[512];
	char fstype[64];
	char mntoptions[256];
	int dump_frequency;
	int fsck_order;
	FILE *fp;
	int n = 0;

	fp = fopen("/proc/mounts", "r");
	if (!fp)
		return -errno;

	while (fgets(line, sizeof(line), fp)) {
		if (sscanf(line, "%s %s %s %s %d %d\n", fsname, mountpoint,
			fstype, mntoptions, &dump_frequency,
			&fsck_order) != 6)
			continue;
		if (strcmp(fstype, "cgroup") && strcmp(fstype, "cgroup2"))
			continue;

		n++;
		*roots = (char **)realloc(*roots, n * sizeof(char *));
		(*roots)[n - 1] = strdup(mountpoint);
	}

	*nentries = n;
	fclose(fp);

	return 0;
}

void cgroup_free_roots(char **roots, int nentries)
{
	int i;
	for (i = 0; i < nentries; i++)
		free(roots[i]);
	free(roots);
}

long cgroup_cgroupid(const char *cgroup_path)
{
	int err;
	struct stat st;
	err = stat(cgroup_path, &st);
	return err ? -errno : st.st_ino;
}

long cgroup_cgroupid2(const char *mntpoint, const char *cgroup_path)
{
	char path[512];
	snprintf(path, sizeof(path) - 1, "%s/%s", mntpoint, cgroup_path);
	return cgroup_cgroupid(path);
}

int for_each_cgroup(const char *root)
{
	int err = 0;
	DIR *dir;
	struct dirent *dirent;
	char *path;
	struct stat st;
	size_t path_len;

	if (!root)
		return -EINVAL;

	lstat(root, &st);
	if (!S_ISDIR(st.st_mode))
		return -EINVAL;

	path = malloc(PATH_MAX);
	snprintf(path, PATH_MAX - 1, "%s/", root);

	lstat(path, &st);
	if (!S_ISDIR(st.st_mode)) {
		free(path);
		return -ENOENT;
	}

	dir = opendir(path);
	if (!dir) {
		err = -errno;
		goto error;
	}

	path_len = strlen(path);

	/* If the directory path doesn't end with a slash, append a slash. */
	if (path[path_len - 1] != '/') {
		path[path_len] = '/';
		path[++path_len] = '\0';
	}

	while ((dirent = readdir(dir)) != NULL) {
		if (!strcmp(dirent->d_name, ".") || !strcmp(dirent->d_name, ".."))
			continue;
		strncpy(path + path_len, dirent->d_name, PATH_MAX - path_len);
		lstat(path, &st);
		if (!S_ISDIR(st.st_mode))
			continue;
		printf("%s\n", path);
		for_each_cgroup(path);
	}

error:
	closedir(dir);
	free(path);
	return err;
}

int cgroup_proc_for_each_cgroup_entry(pid_t pid, void (*callback)(const struct proc_cgroup *cgrp,
								  void *arg),
				      void *arg)
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
		callback(&cgrp, arg);
	}

	fclose(f);
	return lines;
}
