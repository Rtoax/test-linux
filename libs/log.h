#pragma once
#include <stdio.h>
#include <errno.h>
#include <sys/types.h>
#include <unistd.h>

#define LOG_ERROR(err, msg) do { \
		errno = err; \
		perror(msg); \
		exit(-1); \
	} while (0)

#define log_parent(fmt...)  do{ \
		printf("\033[33m[PARENT][%d]", getpid()); \
		printf(fmt); \
		printf("\033[m"); \
	} while (0)

#define log_child(fmt...)  do{ \
		printf("\033[32m[CHILD][%d]", getpid()); \
		printf(fmt); \
		printf("\033[m"); \
	} while (0)

#define log_err(fmt, ...)				\
	do {								\
	fprintf(stderr,						\
		"ERROR: %s(%d): " fmt "\n",		\
		__FILE__,						\
		__LINE__, ##__VA_ARGS__);		\
	} while (0)

#define debug() fprintf(stdout, "[%s:%s %d]\n", __FILE__, __func__, __LINE__)
