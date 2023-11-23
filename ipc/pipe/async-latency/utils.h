#ifndef __UTILS_H
#define __UTILS_H

#include <stdio.h>
#include <sys/time.h>
#include <stdarg.h>

enum {
	__LV_INFO,
	__LV_WARNING,
	__LV_ERR,
	__LV_DEBUG,
};

#define log_info(fmt...) ___debug_log(__LV_INFO, __FILE__, __func__ ,__LINE__, fmt)
#define log_warn(fmt...) ___debug_log(__LV_WARNING, __FILE__, __func__ ,__LINE__, fmt)
#define log_error(fmt...) ___debug_log(__LV_ERR, __FILE__, __func__ ,__LINE__, fmt)
#define log_debg(fmt...) ___debug_log(__LV_DEBUG, __FILE__, __func__ ,__LINE__, fmt)


int gettimeval(struct timeval *tv);

double statistic_throughput(char *description, struct timeval *before,
	struct timeval *after, unsigned long int bytes, long int npkg);

int ___debug_log(int level, char *file, const char *func, int line, char *fmt, ...);

#endif
