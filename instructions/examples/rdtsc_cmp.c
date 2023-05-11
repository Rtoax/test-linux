#include <stdio.h>
#include "rdtsc.h"

#include "utils.h"

#define TEST_NLOOP	10000000

int main(void)
{
	uint64_t i;
	uint64_t tscp, tsc;
	struct timeval start, end;

	/**
	 * rdtsc is faster than rdtscp
	 * see
	 * https://www.felixcloutier.com/x86/rdtscp
	 * https://www.felixcloutier.com/x86/rdtsc
	 */
	uint32_t rcx = 0;
	gettimeofday(&start, NULL);
	for (i = 0; i < TEST_NLOOP; i++) {
		tscp = rdtscp(&rcx);
	}
	gettimeofday(&end, NULL);
	print_diff_tv("           rdtscp ", &end, &start);

	gettimeofday(&start, NULL);
	for (i = 0; i < TEST_NLOOP; i++) {
		tscp = rdtscp_ignore_rcx();
	}
	gettimeofday(&end, NULL);
	print_diff_tv("rdtscp ignore rcx ", &end, &start);

	gettimeofday(&start, NULL);
	for (i = 0; i < TEST_NLOOP; i++) {
		tsc = rdtsc();
	}
	gettimeofday(&end, NULL);
	print_diff_tv("            rdtsc ", &end, &start);

	return 0;
}

