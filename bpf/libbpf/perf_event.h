#pragma once

#define STACK_MAP	1
#define MAX_IPS		8192

struct ipcount {
	unsigned long ip;
	unsigned int count;
};
