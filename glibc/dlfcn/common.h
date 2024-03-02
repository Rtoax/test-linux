#pragma once

#include <stdio.h>

#define __unused __attribute__((unused))

#define debug() do { \
	printf("%s:%s:%d\n", __FILE__, __func__, __LINE__); \
	} while (0)
