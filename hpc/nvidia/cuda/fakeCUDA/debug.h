#pragma once
#include <stdio.h>

#ifdef DEBUG
# define LOG_DEBUG(fmt...) do {	\
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
