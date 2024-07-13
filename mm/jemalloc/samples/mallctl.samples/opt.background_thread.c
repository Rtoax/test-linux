#include <stdio.h>
#include <jemalloc/jemalloc.h>

//opt.background_thread (bool) r-
//	Internal background worker threads enabled/disabled. Because of potential circular dependencies, enabling background
//	thread using this option may cause crash or deadlock during initialization. For a reliable way to use this feature,
//	see background_thread for dynamic control options and details. This option is disabled by default.


void get_jemalloc_opt_background_thread(bool *enable) {
	/* let jemalloc do purging asynchronously, required when there's no traffic
	 * after flushdb */
	size_t size = sizeof(bool);
	je_mallctl("opt.background_thread", enable, &size, NULL, 0);
}

int main(int argc,char **argv)
{
	bool enable = true;

	get_jemalloc_opt_background_thread(&enable);
	printf("enable = %d\n", enable);
}

