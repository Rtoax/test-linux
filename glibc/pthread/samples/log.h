#pragma once

#include <stdio.h>
#include <errno.h>

#define LOG_ERROR(err, msg) do { \
		errno = err; \
		perror(msg); \
		exit(-1); \
	} while (0)

#define log_parent(fmt...)  do{ \
		printf("\033[33m[%d]", getpid()); \
		printf(fmt); \
		printf("\033[m"); \
	} while (0)
#define log_child(fmt...)  do{ \
		printf("\033[32m[%d]", getpid()); \
		printf(fmt); \
		printf("\033[m"); \
	} while (0)

