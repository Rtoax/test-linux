#include <stdio.h>
#include <sys/vlimit.h>
#include <sys/resource.h>

/**
 * LIM_CPU Maximum CPU time. Same as RLIMIT_CPU for setrlimit.
 * LIM_FSIZE Maximum fle size. Same as RLIMIT_FSIZE for setrlimit.
 * LIM_DATA Maximum data memory. Same as RLIMIT_DATA for setrlimit.
 * LIM_STACK Maximum stack size. Same as RLIMIT_STACK for setrlimit.
 * LIM_CORE Maximum core fle size. Same as RLIMIT_COR for setrlimit.
 * LIM_MAXRSS Maximum physical memory. Same as RLIMIT_RSS for setrlimit.
 */

int main(void)
{
	struct rlimit rlimit;

	printf("%d\n", vlimit(LIM_CPU, 256));

	getrlimit(LIM_CPU, &rlimit);

	printf("rlim_cur = %ld\n", rlimit.rlim_cur);
	printf("rlim_max = %ld\n", rlimit.rlim_max);

	return 0;
}
