// SPDX-License-Identifier: GPL-2.0-or-later
/* Copyright (C) 2026 Rong Tao. All rights reserved. */
#pragma once
#include <stdio.h>
#include <syslog.h>
#include "utils.h"

#ifdef DEBUG
#define pc_debug(fmt...) pc_log(LOG_DEBUG, __FILE__, __func__, __LINE__, fmt)
#else
#define pc_debug(fmt...) \
	do {             \
	} while (0)
#endif
#define pc_info(fmt...) pc_log(LOG_INFO, __FILE__, __func__, __LINE__, fmt)
#define pc_notice(fmt...) pc_log(LOG_NOTICE, __FILE__, __func__, __LINE__, fmt)
#define pc_warning(fmt...) \
	pc_log(LOG_WARNING, __FILE__, __func__, __LINE__, fmt)
#define pc_error(fmt...) pc_log(LOG_ERR, __FILE__, __func__, __LINE__, fmt)
#define pc_crit(fmt...) pc_log(LOG_CRIT, __FILE__, __func__, __LINE__, fmt)
#define pc_alert(fmt...) pc_log(LOG_ALERT, __FILE__, __func__, __LINE__, fmt)
#define pc_emerg(fmt...) pc_log(LOG_EMERG, __FILE__, __func__, __LINE__, fmt)

void init_syslog(void);
void close_syslog(void);

__printf(5, 6) void pc_log(int level, const char *file, const char *func,
			   unsigned long int line, char *fmt, ...);
