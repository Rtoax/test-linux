/**
 * https://access.redhat.com/documentation/en-us/red_hat_enterprise_linux_for_real_time/7/html/reference_guide/using_the_sched_setaffinity_system_call_to_set_processor_affinity
 */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <sched.h>

int main(int argc, char **argv)
{
	int i, online = 0;
	ulong ncores = sysconf(_SC_NPROCESSORS_CONF);
	cpu_set_t *setp = CPU_ALLOC(ncores);
	ulong setsz = CPU_ALLOC_SIZE(ncores);

	CPU_ZERO_S(setsz, setp);

	if (sched_getaffinity(getpid(), setsz, setp) == -1) {
		perror("sched_getaffinity(2) failed");
		exit(errno);
	}

	for (i = 0; i < CPU_COUNT_S(setsz, setp); i++) {
		if (CPU_ISSET_S(i, setsz, setp))
			online++;
	}

	printf("%ld cores configured, %d cpus allowed in affinity mask\n",
	       ncores, online);
	CPU_FREE(setp);

	return 0;
}
