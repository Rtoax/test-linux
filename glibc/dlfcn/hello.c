#include <stdio.h>
#include <dlfcn.h>
#include <stdlib.h>
#include "common.h"


int main(void)
{
	void *dp;
	void (*init)(void);
	void (*done)(void);

	dp = dlopen("./libhello.so", RTLD_LAZY);
	if (NULL == dp) {
		printf("%s\n", dlerror());
		exit(1);
	}
	debug();

	init = dlsym(dp, "init");
	done = dlsym(dp, "done");

	init();
	done();

	return 0;
}
