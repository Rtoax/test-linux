// SPDX-License-Identifier: (LGPL-2.1 OR BSD-2-Clause)
#include <stdio.h>
#include <fcntl.h>
#include <string.h>
#include <errno.h>

#include "oom_helpers.h"

/*
 * /proc/<pid>/oom_score_adj set to OOM_SCORE_ADJ_MIN disables oom killing for
 * pid.
 */
#define OOM_SCORE_ADJ_MIN	(-1000)
#define OOM_SCORE_ADJ_MAX	1000

/*
 * /proc/<pid>/oom_adj set to -17 protects from the oom killer for legacy
 * purposes.
 */
#define OOM_DISABLE (-17)

/* inclusive(包容性) */
#define OOM_ADJUST_MIN (-16)
#define OOM_ADJUST_MAX 15


static int set_int_to_file(char *file, int val)
{
	int ret, err = 0;
	FILE *fp;

	fp = fopen(file, "w");
	if (!fp) {
		fprintf(stderr, "fopen(%s) %m\n", file);
		return -errno;
	}
	ret = fprintf(fp, "%d", val);
	if (ret <= 0) {
		fprintf(stderr, "fprintf(%s) %m\n", file);
		err = -errno;
	}
	fclose(fp);
	return err;
}

static int get_int_from_file(char *file)
{
	int val, ret;
	FILE *fp;

	fp = fopen(file, "r");
	if (!fp) {
		fprintf(stderr, "fopen(%s) %m\n", file);
		return -1;
	}
	ret = fscanf(fp, "%d", &val);
	if (ret == EOF) {
		fprintf(stderr, "fscanf(%s) %m\n", file);
	}
	fclose(fp);
	return val;
}

/**
 * oom_adj: This parameter is used to adjust the OOM killer's badness score
 * for a process. It ranges from -17 to 15, where -17 means the process is
 * completely immune to the OOM killer, and 15 means the process is highly
 * likely to be killed.
 */
int set_oom_adj(pid_t pid, int val)
{
	char buf[128];

	if ((val < OOM_ADJUST_MIN || val > OOM_ADJUST_MAX) &&
	     val != OOM_DISABLE) {
		fprintf(stderr, "invalid oom_adj %d\n", val);
		return -EINVAL;
	}

	snprintf(buf, 128, "/proc/%d/oom_adj", pid);
	return set_int_to_file(buf, val);
}

int disable_oom_by_adj(pid_t pid)
{
	return set_oom_adj(pid, OOM_DISABLE);
}

int get_oom_adj(pid_t pid)
{
	char buf[128];
	snprintf(buf, 128, "/proc/%d/oom_adj", pid);
	return get_int_from_file(buf);
}

/**
 * oom_score: This read-only parameter shows the current OOM score for a
 * process. It ranges from 0 to 1000, where a higher score indicates a
 * higher likelihood of being killed by the OOM killer.
 */
int get_oom_score(pid_t pid)
{
	char buf[128];
	snprintf(buf, 128, "/proc/%d/oom_score", pid);
	return get_int_from_file(buf);
}

/**
 * oom_score_adj: This parameter replaces oom_adj in newer kernels and
 * provides a finer control over the OOM killer's behavior. It ranges
 * from -1000 to 1000, where -1000 means the process is completely
 * immune to the OOM killer, and 1000 means the process is highly likely
 * to be killed.
 */
int set_oom_score_adj(pid_t pid, int val)
{
	char buf[128];

	if (val < OOM_SCORE_ADJ_MIN || val > OOM_SCORE_ADJ_MAX) {
		fprintf(stderr, "invalid oom_score_adj %d\n", val);
		return -EINVAL;
	}

	snprintf(buf, 128, "/proc/%d/oom_score_adj", pid);
	return set_int_to_file(buf, val);
}

int disable_oom_by_score_adj(pid_t pid)
{
	return set_oom_score_adj(pid, OOM_SCORE_ADJ_MIN);
}

int get_oom_score_adj(pid_t pid)
{
	char buf[128];
	snprintf(buf, 128, "/proc/%d/oom_score_adj", pid);
	return get_int_from_file(buf);
}
