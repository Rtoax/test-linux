#pragma once

#define MAX_ENTRIES	2048

struct event_t {
	int pid;
	int uid;
	char comm[16];
	char filename[64];
	int ret;
};
