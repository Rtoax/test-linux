// SPDX-License-Identifier: GPL-3.0
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/types.h>
#include <unistd.h>

#define TRACEFS_PIPE    "/sys/kernel/tracing/trace_pipe"
#define DEBUGFS_PIPE    "/sys/kernel/debug/tracing/trace_pipe"

/**
 * cb: call back, if return non-zero value, while done
 */
int read_trace_pipe_cb(int (*cb)(const char *str, void *arg), void *arg)
{
	size_t buflen, n;
	char *pipefile, *buf;
	FILE *fp;
	int err;

	if (access(TRACEFS_PIPE, F_OK) == 0)
		pipefile = TRACEFS_PIPE;
	else
		pipefile = DEBUGFS_PIPE;

	fp = fopen(pipefile, "r");
	if (!fp) {
		fprintf(stderr, "failed to open %s\n", pipefile);
		return -errno;
	}

	buf = NULL;

	while ((n = getline(&buf, &buflen, fp) >= 0) || errno == EAGAIN) {
		if (n > 0) {
			err = cb(buf, arg);
			if (err)
				break;
		}
	}
	free(buf);
	fclose(fp);
	return 0;
}

static int trace_pipe_cb(const char *str, void *arg)
{
	printf("%s", str);
	return 0;
}

int read_trace_pipe(void)
{
	return read_trace_pipe_cb(trace_pipe_cb, NULL);
}
