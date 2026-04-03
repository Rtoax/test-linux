#pragma once
#include <stdio.h>
#include <unistd.h>
#include <sys/select.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <errno.h>
#include <sys/inotify.h>
#include <signal.h>
#include <stdlib.h>
#include <getopt.h>
#include <stdbool.h>
#include <unistd.h>
#include <string.h>
#include <syslog.h>
#include <assert.h>
#include "rb.h"

#define __unused __attribute__((unused))

#define ARRAY_SIZE(arr) (sizeof(arr)/sizeof(arr[0]))

#define ROUND_DOWN(x, m) ((x) & ~((m) - 1))
#define ROUND_UP(x, m) (((x) + (m) - 1) & ~((m) - 1))

#define stdio_log(fmt...) do { \
		fprintf(stdout, fmt); \
	} while (0)

extern bool debug;

/* journalctl */
#define ldebug(fmt...) do { \
		if (!debug) \
			break; \
		stdio_log(fmt); \
		syslog(LOG_DEBUG, fmt); \
	} while (0)
#define linfo(fmt...) do { \
		stdio_log(fmt); \
		syslog(LOG_INFO, fmt); \
	} while (0)
#define lwarning(fmt...) do { \
		stdio_log(fmt); \
		syslog(LOG_WARNING, fmt); \
	} while (0)
#define lerror(fmt...) do { \
		stdio_log(fmt); \
		syslog(LOG_ERR, fmt); \
	} while (0)

#define power_of_2(v)                    \
	({                               \
		unsigned long __ret = 2; \
		while (__ret < v)        \
			__ret <<= 1;     \
		__ret;                   \
	})

struct addr_space;

void init_addr_space(struct addr_space **space, unsigned long granularity);
void insert_addr(struct addr_space *space, unsigned long addr,
		 unsigned long quota);
bool has_addr(struct addr_space *space, unsigned long addr);
void print_addr_space(struct addr_space *space, FILE *fp);
void plot_space(FILE *fp, struct addr_space *space, unsigned long col,
		const char *f_bin, bool text_only);
void quota_normalization(struct addr_space *space, unsigned long min,
			 unsigned long max);
void addr_normalization(struct addr_space *space, unsigned long min,
			unsigned long max);

unsigned long strtoaddr(const char *s);

void print_ansi(void);
