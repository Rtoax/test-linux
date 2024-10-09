#pragma once

#include <stdio.h>

#define log(fmt...) ({	\
		int ___n = 0;	\
		___n += fprintf(stdout, "[%s]%s:%d ", __FILE__,	\
				__func__, __LINE__);	\
		___n += fprintf(stdout, fmt);	\
		___n;	\
	})

