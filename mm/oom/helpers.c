#include <stdio.h>
#include <fcntl.h>
#include <string.h>
#include <errno.h>

#include "helpers.h"

#define OOM_DISABLE (-17)
#define OOM_ADJUST_MIN (-16)
#define OOM_ADJUST_MAX 15


/**
 * oom_adj: This parameter is used to adjust the OOM killer's badness score
 * for a process. It ranges from -17 to 15, where -17 means the process is
 * completely immune to the OOM killer, and 15 means the process is highly
 * likely to be killed.
 */
int set_oom_adj(pid_t pid, int val)
{
	int ret, err = 0;
	FILE *fp;
	char buf[128];

	if ((val < OOM_ADJUST_MIN || val > OOM_ADJUST_MAX) &&
	     val != OOM_DISABLE) {
		fprintf(stderr, "invalid oom_adj %d\n", val);
		return -EINVAL;
	}

	snprintf(buf, 128, "/proc/%d/oom_adj", pid);
	fp = fopen(buf, "w");
	if (!fp) {
		fprintf(stderr, "fopen(%s) %m\n", buf);
		return -errno;
	}
	ret = fprintf(fp, "%d", val);
	if (ret <= 0) {
		fprintf(stderr, "fprintf(%s) %m\n", buf);
		err = -errno;
	}
	fclose(fp);
	return err;
}

int disable_oom(pid_t pid)
{
	return set_oom_adj(pid, OOM_DISABLE);
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
