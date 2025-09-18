// SPDX-License-Identifier: GPL-3.0
/* Copyright (c) 2025 Rong Tao */
#pragma once
#include <stdio.h>
#include <stdbool.h>

#ifndef DEBUG
# define DEBUG	1
#endif
#ifdef DEBUG
# define LOG_DEBUG(fmt...) do {	\
		if (!fakecuda_debug)	\
			break;	\
		fprintf(stderr, "\033[2m");	\
		fprintf(stderr, "fakeCUDA: DEBUG: [%s:%d] ", __func__, __LINE__);	\
		fprintf(stderr, fmt);	\
		fprintf(stderr, "\033[m");	\
	} while (0)
#else
# define LOG_DEBUG(fmt...) do {} while (0)
#endif

#define LOG_ERROR(fmt...) do {	\
		fprintf(stderr, "\033[31m");	\
		fprintf(stderr, "fakeCUDA: ERROR: [%s:%d] ", __func__, __LINE__);	\
		fprintf(stderr, fmt);	\
		fprintf(stderr, "\033[m");	\
	} while (0)

extern bool fakecuda_debug;
