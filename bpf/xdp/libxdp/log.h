// SPDX-License-Identifier: GPL-3.0
#pragma once

#include <stdio.h>
#include <stdint.h>

#define pr_inf(fmt...) do { \
		fprintf(stdout, "\033[1;32m"); \
		fprintf(stdout, fmt); \
		fprintf(stdout, "\033[m"); \
		fflush(stdout); \
	} while (0)

#define pr_err(fmt...) do { \
		fprintf(stderr, "\033[1;31m"); \
		fprintf(stderr, fmt); \
		fprintf(stderr, "\033[m"); \
	} while (0)

#define pr_dbg(fmt...) do { \
		fprintf(stdout, "\033[2m"); \
		fprintf(stdout, fmt); \
		fprintf(stdout, "\033[m"); \
		fflush(stdout); \
	} while (0)
