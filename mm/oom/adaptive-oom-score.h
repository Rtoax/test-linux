#pragma once

#define TASK_COMM_LEN   64

struct pf_event_t {
	int pid;
	char comm[TASK_COMM_LEN];
};
