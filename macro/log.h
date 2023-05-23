#pragma once

#include <stdio.h>

#define log_err(fmt, ...)				\
	do {								\
	fprintf(stderr,						\
		"ERROR: %s(%d): " fmt "\n",		\
		__FILE__,						\
		__LINE__, ##__VA_ARGS__);		\
	} while (0)

#define debug() fprintf(stdout, "[%s:%s %d]\n", __FILE__, __func__, __LINE__)

