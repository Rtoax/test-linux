#pragma once

struct data_t {
	int pid;
	int uid;
	int counter;
	char command[16];
	char message[12];
};

struct config_st {
	__u32 action;
	int ifindex;
	__u32 options;
	char message[12];
};
