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

extern bool debug;

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
