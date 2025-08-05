// SPDX-License-Identifier: (LGPL-2.1 OR BSD-2-Clause)
/* Copyright (c) 2025 Rong Tao */
#include <assert.h>
#include <dirent.h>
#include <errno.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <string.h>
#include "cgroup_helpers.h"


int cgroup_get_roots(char ***roots)
{
	char line[2048];
	char fsname[128];
	char mountpoint[PATH_MAX];
	char fstype[64];
	char mntoptions[256];
	int dump_frequency;
	int fsck_order;
	FILE *fp;
	int n = 0;

	fp = fopen("/proc/mounts", "r");
	if (!fp)
		return -errno;

	*roots = NULL;

	while (fgets(line, sizeof(line), fp)) {
		if (sscanf(line, "%s %s %s %s %d %d\n", fsname, mountpoint,
			fstype, mntoptions, &dump_frequency,
			&fsck_order) != 6)
			continue;

		/* Only need cgroup or cgroup2 */
		if (strcmp(fstype, "cgroup") && strcmp(fstype, "cgroup2"))
			continue;

		n++;
		*roots = (char **)realloc(*roots, n * sizeof(char *));
		(*roots)[n - 1] = strdup(mountpoint);
	}

	fclose(fp);

	return n;
}

int cgroup_free_roots(char **roots, int nentries)
{
	int i;

	if (!roots || nentries <= 0)
		return -EINVAL;

	for (i = 0; i < nentries; i++)
		free(roots[i]);
	free(roots);

	return 0;
}

long cgroup_cgroupid_of_path(const char *cgroup_path)
{
	int err;
	struct stat st;
	/* The inode of the cgroup folder is the groupid */
	err = stat(cgroup_path, &st);
	return err ? -errno : st.st_ino;
}

long cgroup_cgroupid_of_mnt_path(const char *mntpoint, const char *cgroup_path)
{
	char path[PATH_MAX];
	snprintf(path, sizeof(path) - 1, "%s/%s", mntpoint, cgroup_path);
	return cgroup_cgroupid_of_path(path);
}

static int for_each_cgroup_match(const char *root, int (*match)(const char *path,
								void *arg),
				 void *arg)
{
	int err = 0;
	DIR *dir;
	struct dirent *dirent;
	char *path;
	struct stat st;
	size_t path_len;

	if (!root || !match)
		return -EINVAL;

	err = lstat(root, &st);
	if (err)
		return -errno;
	if (!S_ISDIR(st.st_mode))
		return -EINVAL;

	path = malloc(PATH_MAX);
	assert(path && "Malloc failed");

	snprintf(path, PATH_MAX - 1, "%s/", root);

	err = lstat(path, &st);
	if (err)
		return -errno;
	if (!S_ISDIR(st.st_mode)) {
		free(path);
		return -ENOENT;
	}

	dir = opendir(path);
	if (!dir) {
		err = -errno;
		goto done;
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
		err = lstat(path, &st);
		if (err)
			continue;
		if (!S_ISDIR(st.st_mode))
			continue;
#ifdef DEBUG
		fprintf(stderr, "%s\n", path);
#endif
		if (match(path, arg)) {
			err = 0;
			goto done;
		}
		err = for_each_cgroup_match(path, match, arg);
		if (err)
			goto done;
	}

	err = 0;
done:
	closedir(dir);
	free(path);
	return err;
}

struct match_cgroupid_arg {
	long cgroupid;
	bool match;
	char path[PATH_MAX];
};

static int match_cgroupid(const char *path, void *arg)
{
	long cgroupid;
	struct match_cgroupid_arg *a = arg;

	cgroupid = cgroup_cgroupid_of_path(path);
#ifdef DEBUG
	fprintf(stderr, "%ld:%ld %s\n", cgroupid, a->cgroupid, path);
#endif
	if (cgroupid == a->cgroupid) {
		snprintf(a->path, PATH_MAX, path);
		a->match = true;
		return 1;
	}
	return 0;
}

int cgroup_cgroup_path(long cgroupid, char *buf, size_t buf_len)
{
	char **roots;
	int nroots, i;
	struct match_cgroupid_arg arg = {};
	bool found = false;

	arg.cgroupid = cgroupid;
	arg.match = false;

	nroots = cgroup_get_roots(&roots);

	for (i = 0; i < nroots; i++) {
#ifdef DEBUG
		fprintf(stderr, "root --- %s\n", roots[i]);
#endif
		for_each_cgroup_match(roots[i], match_cgroupid, &arg);
		if (arg.match) {
			strncpy(buf, arg.path, buf_len);
			found = true;
			break;
		}
	}

	cgroup_free_roots(roots, nroots);

	return found ? 0 : -ENOENT;
}

int cgroup_proc_for_each_cgroup_entry(pid_t pid, void (*callback)(const struct cgroup_proc_entry *cgrp,
								  void *arg),
				      void *arg)
{
	char line[512];
	char proc[64];
	FILE *f;
	int lines = 0;
	struct cgroup_proc_entry cgrp;

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

		memset(&cgrp, 0, sizeof(cgrp));

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
