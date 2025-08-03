#pragma once

#define PERF_MAX_STACK_DEPTH	127
#define MAX_IPS		8192

struct ipcount {
	unsigned long ip;
	unsigned int count;
};
