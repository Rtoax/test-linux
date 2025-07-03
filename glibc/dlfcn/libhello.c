#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "common.h"

int local_i = 123;
static long __unused static_i = 1024;
static char __unused *static_s = "you";
extern int extern_i;

void init(void)
{
	local_i++;
	static_i++;
	static_s++;
#ifdef ERROR
	/* undefined symbol: extern_i */
	extern_i++;
#endif
	printf("\n");
	debug("\n");
}

void done(void)
{
	debug("\n");
}
