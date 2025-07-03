#pragma once
#include <stdio.h>

#define __unused __attribute__((unused))

#define debug(fmt...) do {						\
		printf("%s:%s:%d", __FILE__, __func__, __LINE__);	\
		printf(fmt);						\
	} while (0)
