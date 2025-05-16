#pragma once

#define TASK_COMM_LEN	16
#define MAX_ENTRIES	2048
#define PATH_MAX	4096

#ifdef PARSE_AUXV
struct auxv_entry {
#define AT_NULL	0
	unsigned long type;
	unsigned long val;
};
#endif

struct event_t {
	int pid;
	int uid;
	char comm[TASK_COMM_LEN];
	char comm2[TASK_COMM_LEN];
	char filename[64];
	char cwd[4096];
#ifdef PARSE_AUXV
	struct auxv_entry auxv;
#endif
	int ret;
};
