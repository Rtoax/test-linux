#pragma once

#include <stdio.h>
#include <unistd.h>
#include <syscall.h>

#define gettid() syscall(__NR_gettid)

#define log_enqueue(fmt...) do{ \
		printf("\033[33m[%ld]", gettid()); \
		printf(fmt); \
		printf("\033[m"); \
	} while (0)
#define log_dequeue(fmt...) do{ \
		printf("\033[32m[%ld]", gettid()); \
		printf(fmt); \
		printf("\033[m"); \
	} while (0)

int parse_flags(int argc, char *argv[]);
