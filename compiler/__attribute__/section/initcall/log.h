#ifndef __LOG_H
#define __LOG_H 1

#include <stdio.h>

#define log(fmt...) ({ \
		int ___n = 0;\
		___n += fprintf(stdout, "[%s]%s:%d ", __FILE__, __func__, __LINE__);\
		___n += fprintf(stdout, fmt);\
		___n;\
	})

#endif /*<__LOG_H>*/