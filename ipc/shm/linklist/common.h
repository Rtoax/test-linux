#pragma once

#include <mlinklist.h>

#define LINKLIST_SIZE   100
#define MMAP_FILENAME   "test.mmap"

struct ll_node {
	int i;
	union {
		struct ll_node *next;
		size_t offset;
	};
};

