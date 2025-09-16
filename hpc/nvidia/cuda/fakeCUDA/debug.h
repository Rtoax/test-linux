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
		fprintf(stderr, "fakeCUDA: DEBUG: [%s:%d] ", __func__, __LINE__);	\
		fprintf(stderr, fmt);	\
	} while (0)
#else
# define LOG_DEBUG(fmt...) do {} while (0)
#endif

#define LOG_ERROR(fmt...) do {	\
		fprintf(stderr, "fakeCUDA: ERROR: [%s:%d] ", __func__, __LINE__);	\
		fprintf(stderr, fmt);	\
	} while (0)

extern bool fakecuda_debug;
