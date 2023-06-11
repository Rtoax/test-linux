#define _GNU_SOURCE
#include <sched.h>

int sys_pthread_set_prio(int prio, int policy)
{
	int rc = SUCCESS;
#ifdef PRINT_DBG_OK
	int i;
	cpu_set_t cpuset;
#endif

	if (prio) {
		struct sched_param sched_param;

		print_log("priority: %d, policy: %d", prio, policy);

		sched_param.sched_priority = prio;

		if ((rc = pthread_setschedparam(pthread_self(), policy, &sched_param))) {
			print_err("priority is not changed: %d", rc);
			return rc;
		}

#ifdef PRINT_DBG_OK
		/* check the actual affinity mask assigned to the thread */

		CPU_ZERO(&cpuset);

		rc = pthread_getaffinity_np(pthread_self(), sizeof(cpu_set_t), &cpuset);
		if (rc) {
			print_err("pthread_getaffinity_np failed: %d", rc);
			perror("pthread_getaffinity_np failed");
		}

		print_log("%s() affinity set: ", __func__);

		for (i = 0; i < CPU_SETSIZE; i++) {
			if (CPU_ISSET(i, &cpuset)) {
				print_log("    CPU %d\n", i);
			}
		}

		if (!CPU_ISSET(0, &cpuset)) {
			print_err("affinity failed");
		}
#endif  /* PRINT_DBG_OK */
	}

	return rc;
}
