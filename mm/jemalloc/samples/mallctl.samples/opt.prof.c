#include <stdio.h>
#include <jemalloc/jemalloc.h>

//opt.prof (bool) r- [--enable-prof]	简明扼要
//	Memory profiling enabled/disabled. If enabled, profile memory allocation activity. See the opt.prof_active option for
//	on-the-fly activation/deactivation. See the opt.lg_prof_sample option for probabilistic sampling control. See the opt.
//	prof_accum option for control of cumulative sample reporting. See the opt.lg_prof_interval option for information on
//	interval-triggered profile dumping, the opt.prof_gdump option for information on high-water-triggered profile dumping
//	, and the opt.prof_final option for final profile dumping. Profile output is compatible with the jeprof command,
//	which is based on the pprof that is developed as part of the gperftools package. See HEAP PROFILE FORMAT for heap
//	profile format documentation.

void get_jemalloc_opt_prof(bool *enable) {
	size_t size = sizeof(bool);
	je_mallctl("opt.prof", enable, &size, NULL, 0);
}

int main(int argc,char **argv)
{
	bool enable = true;

	get_jemalloc_opt_prof(&enable);
	printf("enable = %d\n", enable);
}



