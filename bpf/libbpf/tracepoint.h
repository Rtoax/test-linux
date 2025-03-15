#pragma once

#define MAX_ENTRIES	2048
#define PATH_MAX	4096

struct event_t {
	int pid;
	int uid;
	char comm[16];
	char filename[64];
	char cwd[4096];
	int ret;
};
