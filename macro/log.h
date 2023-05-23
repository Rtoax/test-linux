#pragma once

#define log_err(fmt, ...)				\
	do {								\
	fprintf(stderr,						\
		"ERROR: %s(%d): " fmt "\n",		\
		__FILE__,						\
		__LINE__, ##__VA_ARGS__);		\
	} while (0)

