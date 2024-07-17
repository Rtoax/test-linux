#pragma once

#include <mlinklist.h>

#define LINKLIST_SIZE   100
#define MMAP_FILENAME   "test.mmap"

#define ARRAY_SIZE(arr) (sizeof(arr) / sizeof(arr[0]))

struct ll_node {
	int i;
	union {
		struct ll_node *next;
		size_t offset;
	};
};

