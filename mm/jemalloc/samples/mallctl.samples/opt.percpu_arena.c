#include <stdio.h>
#include <jemalloc/jemalloc.h>
#include "swapper.h"

//opt.percpu_arena (const char *) r-
//	Per CPU arena mode. Use the “percpu” setting to enable this feature, which uses number of CPUs to determine
//	number of arenas, and bind threads to arenas dynamically based on the CPU the thread runs on currently. “phycpu”
//	setting uses one arena per physical CPU, which means the two hyper threads on the same CPU share one arena. Note that
//	no runtime checking regarding the availability of hyper threading is done at the moment. When set to “disabled”,
//	narenas and thread to arena association will not be impacted by this option. The default is “disabled”.



void get_jemalloc_opt_percpu_arena(char *value) {
	size_t size = 32;
	je_mallctl("opt.percpu_arena", value, &size, NULL, 0);
}


int main(int argc,char **argv)
{
	char value[256] = {"123"};

	get_jemalloc_opt_percpu_arena(value);
	printf("value = %s\n", value);
}


