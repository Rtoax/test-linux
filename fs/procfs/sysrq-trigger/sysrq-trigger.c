// SPDX-License-Identifier: (LGPL-2.1 OR BSD-2-Clause)
/* Copyright (c) 2025 Rong Tao */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <libgen.h>
#include <errno.h>
#include <unistd.h>

#define PROC_SYSRQ_TRIGGER	"/proc/sysrq-trigger"

int echo_proc_sysrq_trigger(char cmd)
{
	int n, fd;
	char str_cmd[4] = {0};

	fd = open(PROC_SYSRQ_TRIGGER, O_RDWR | O_NONBLOCK | O_NDELAY);
	if (fd == -1) {
		fprintf(stderr, "ERROR: open %s failed, %m\n", PROC_SYSRQ_TRIGGER);
		return -errno;
	}

	fprintf(stdout, "write %c to %s\n", cmd, PROC_SYSRQ_TRIGGER);

	sprintf(str_cmd, "%c", cmd);

	n = write(fd, str_cmd, 1);
	if (n == -1) {
		fprintf(stderr, "ERROR: write %s failed, %m\n", PROC_SYSRQ_TRIGGER);
		close(fd);
		return -errno;
	}

	close(fd);
	return 0;
}

void usage(void)
{
	printf("\033[1m write [char] to %s\033[m\n", PROC_SYSRQ_TRIGGER);
	printf("   [char]:\n");
#define trigger(cmd, discription)    printf("    %c - %s\n", cmd, discription);
# include "trigger-defs.h"
#undef trigger
}

int main(int argc, char *argv[])
{
	char cmd;

	if (argc == 1) {
		usage();
		return 0;
	}

	cmd = argv[1][0];

	switch (cmd) {
#define trigger(cmd, discription)    case cmd:
# include "trigger-defs.h"
#undef trigger
		echo_proc_sysrq_trigger(cmd);
		break;
	default:
		fprintf(stderr, "ERROR: unknown %c\n", cmd);
		usage();
		break;
	}
	return 0;
}
