// SPDX-License-Identifier: (LGPL-2.1 OR BSD-2-Clause)
#ifndef _GNU_SOURCE
#define _GNU_SOURCE
#endif
#include <assert.h>
#include <fcntl.h>
#include <sched.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

#include "fork_helpers.h"


void try_fork(int vf, char *argv[])
{
	pid_t pid;

	pid = vf ? vfork() : fork();
	if (pid == -1) {
		perror("fork");
		return;
	}

	if (pid == 0) {
		char *_argv[] = {"echo", "child", NULL};
		if (argv)
			execvp(argv[0], argv);
		else
			execvp(_argv[0], _argv);
	}
	waitpid(pid, NULL, 0);
}

void try_popen(char *cmd_buf)
{
	char buf[128] = "uname -rm";
	char line[256] = {0};
	FILE *fp = popen(cmd_buf ?: buf, "r");
	if (fp == NULL) {
		fprintf(stderr, "popen(%s) %m\n", cmd_buf ?: buf);
		return;
	}
	while (fgets(line, 256, fp))
		printf("%s", line);
	pclose(fp);
}

void save_pid(const char *filename, pid_t pid)
{
	FILE *fp = fopen(filename, "w");
	if (!fp) {
		fprintf(stderr, "ERROR: could't open %s, %m", filename);
		kill(pid, SIGKILL);
		assert(fp && "fopen()");
	}
	fprintf(fp, "%d", pid);
	fclose(fp);
}

int load_pid(const char *filename)
{
	int pid;
	FILE *fp = fopen(filename, "r");
	fscanf(fp, "%d", &pid);
	fclose(fp);
	return pid;
}

