#pragma once

#define COMM_SIZE 16

struct syscall_buf {
	u32 serial;
	u64 ts_sec;
	u64 ts_micro;
	u32 syscall;
	u32 status;
	pid_t pid;
	uid_t uid;
	u8 comm[COMM_SIZE];
};

