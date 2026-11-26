// SPDX-License-Identifier: GPL-2.0-or-later
/* Copyright (C) 2022-2026 Rong Tao */
#include <stdarg.h>
#include <libgen.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "log.h"

void init_syslog(void)
{
	setlogmask(LOG_UPTO(LOG_DEBUG));
	openlog("plotcake", LOG_CONS | LOG_PID | LOG_NDELAY, LOG_LOCAL1);
}

void close_syslog(void)
{
	closelog();
}

__printf(5, 6) void pc_log(int level, const char *file, const char *func,
			   unsigned long int line, char *fmt, ...)
{
	va_list va;
	va_start(va, fmt);
	vsyslog(level, fmt, va);
	va_end(va);
}
