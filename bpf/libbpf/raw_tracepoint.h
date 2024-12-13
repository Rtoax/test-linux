#pragma once

struct data_t {
	int pid;
	int uid;
	char comm[16];
	char child_comm[16];
};
