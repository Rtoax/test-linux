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


void try_fork(void)
{
	pid_t pid = fork();
	if (pid == -1) {
		perror("fork");
		return;
	}

	if (pid == 0) {
		char *argv[] = {"echo", "child", NULL};
		execvp(argv[0], argv);
	}
	waitpid(pid, NULL, 0);
}

void try_popen(void)
{
	char buf[128] = "uname -rm";
	char line[256] = {0};
	FILE *fp = popen(buf, "r");
	if (fp == NULL) {
		fprintf(stderr, "popen(%s) %m\n", buf);
		return;
	}
	while (fgets(line, 256, fp))
		printf("%s\n", line);
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

