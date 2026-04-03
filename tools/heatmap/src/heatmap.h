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

struct heatmap_space;

void heatmap_create_space(struct heatmap_space **space,
			  unsigned long granularity);
void heatmap_insert_addr(struct heatmap_space *space, unsigned long addr,
			 unsigned long quota);
bool heatmap_has_addr(struct heatmap_space *space, unsigned long addr);
void heatmap_print_space(struct heatmap_space *space, FILE *fp);
void heatmap_plot_space(FILE *fp, struct heatmap_space *space,
			unsigned long col, const char *f_bin, bool text_only);
void heatmap_quota_normalization(struct heatmap_space *space, unsigned long min,
				 unsigned long max);
void heatmap_addr_normalization(struct heatmap_space *space, unsigned long min,
				unsigned long max);

unsigned long strtoaddr(const char *s);

void heatmap_print_ansis(void);
