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
#include <rb.h>

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

unsigned long power_of_2(unsigned long v);

struct addr_node {
	/* [start, end) */
	unsigned long start, end;

	/* temp to use */
	unsigned long addr;

	unsigned long quota;

	rb_node(struct addr_node) rb_link_node;
};

typedef rb_tree(struct addr_node) addr_tree;

struct addr_space {
	addr_tree tree;

	/* bytes */
	unsigned long granularity;
	unsigned long max_addr, min_addr;
	unsigned long max_quota, min_quota;
};

rb_proto(static __unused, addr_, addr_tree, struct addr_node);

static int __addr_in_node(const struct addr_node *node, unsigned long addr)
{
	if (addr < node->start)
		return 1;
	else if (addr >= node->start && addr < node->end)
		return 0;
	else if (addr >= node->end)
		return -1;

	return 0;
}

static int addr_node_cmp(const struct addr_node *a, const struct addr_node *b)
{
	if (a->addr)
		return __addr_in_node(b, a->addr);

	if (b->addr)
		return __addr_in_node(a, b->addr);

	if (b->end <= a->start)
		return -1;
	else if (a->start < b->end && a->end > b->start)
		return 0;
	else if (a->end <= b->start)
		return 1;

	return 0;
}

rb_gen(static __unused, addr_, addr_tree, struct addr_node, rb_link_node,
       addr_node_cmp);

void init_addr_space(struct addr_space *space, unsigned long granularity);
void insert_addr(struct addr_space *space, unsigned long addr, unsigned long quota);
bool has_addr(struct addr_space *space, unsigned long addr);
void print_addr_space(struct addr_space *space, FILE *fp);
void plot_space(FILE *fp, struct addr_space *space, unsigned long col,
		const char *f_bin, bool text_only);
void quota_normalization(struct addr_space *space,
		unsigned long min, unsigned long max);
void addr_normalization(struct addr_space *space,
		unsigned long min, unsigned long max);

unsigned long strtoaddr(const char *s);

void print_ansi(void);
