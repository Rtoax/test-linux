#include <stdio.h>
#include <stdlib.h>
#include "rdtsc.h"

#include "utils.h"


int main(int argc, char *argv[])
{
	uint64_t i;
	uint64_t tscp, tsc;
	struct timeval start, end;
	unsigned long test_nloop = 10000000;

	fprintf(stderr, "%s [nloop], default: %ld\n", argv[0], test_nloop);

	if (argc > 1) {
		test_nloop = strtoul(argv[1], NULL, 10);
	}

	fprintf(stdout, "NLoop %ld\n", test_nloop);

	/**
	 * rdtsc is faster than rdtscp
	 * see
	 * https://www.felixcloutier.com/x86/rdtscp
	 * https://www.felixcloutier.com/x86/rdtsc
	 */
	uint32_t rcx = 0;
	gettimeofday(&start, NULL);
	for (i = 0; i < test_nloop; i++) {
		tscp = rdtscp(&rcx);
	}
	gettimeofday(&end, NULL);
	print_diff_tv("           rdtscp ", &end, &start, true);

	gettimeofday(&start, NULL);
	for (i = 0; i < test_nloop; i++) {
		tscp = rdtscp_ignore_rcx();
	}
	gettimeofday(&end, NULL);
	print_diff_tv("rdtscp ignore rcx ", &end, &start, true);

	gettimeofday(&start, NULL);
	for (i = 0; i < test_nloop; i++) {
		tsc = rdtsc();
	}
	gettimeofday(&end, NULL);
	print_diff_tv("            rdtsc ", &end, &start, true);

	gettimeofday(&start, NULL);
	for (i = 0; i < test_nloop; i++) {
		tsc = rdtsc_fence();
	}
	gettimeofday(&end, NULL);
	print_diff_tv("    rdtsc ordered ", &end, &start, true);

	(void)tsc;
	(void)tscp;

	return 0;
}

