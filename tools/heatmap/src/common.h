#pragma once

#include <stdio.h>
#include <stdbool.h>
#include <syslog.h>

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


static const char *const ANSI_COLORS_GRAY[] = {
	"\033[48;5;255m",
	"\033[48;5;252m",
	"\033[48;5;250m",
	"\033[48;5;248m",
	"\033[48;5;246m",
	"\033[48;5;244m",
	"\033[48;5;242m",
	"\033[48;5;240m",
	"\033[48;5;238m",
	"\033[48;5;236m",
	"\033[48;5;234m",
	"\033[48;5;232m",
};
static const char *const ANSI_COLORS_RESET = "\033[0m";
#define NR_ANSI ARRAY_SIZE(ANSI_COLORS_GRAY)

static const char *ansi_text[] = {
	" ",
	" ",
	".",
	".",
	"*",
	"*",
	"o",
	"o",
	"O",
	"O",
	"#",
	"#",
};

unsigned long power_of_2(unsigned long v);

void print_ansi(void);
