#pragma once

#define TASK_COMM_LEN	16
#define MAX_ENTRIES	2048
#define PATH_MAX	4096

struct event_t {
	int pid;
	int uid;
	char comm[TASK_COMM_LEN];
	char comm2[TASK_COMM_LEN];
	char filename[64];
	char cwd[4096];
	int ret;
};
