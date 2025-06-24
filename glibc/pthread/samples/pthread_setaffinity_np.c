#ifndef _GNU_SOURCE
#define _GNU_SOURCE
#endif
#include <stdio.h>
#include <math.h>
#include <pthread.h>

cpu_set_t cpuset, cpuget;

double waste_time(long n)
{
	double res = 0;
	long i = 0;

	while (i < n * 200000000) {
		i++;
		res += sqrt(i);
	}
	return res;
}

void *thread_func(void *param)
{
	int ret;

	CPU_ZERO(&cpuset);
	/* cpu 0 is in cpuset now */
	CPU_SET(1, &cpuset);

	/* bind process to processor 0 */
	ret = pthread_setaffinity_np(pthread_self(), sizeof(cpu_set_t), &cpuset);
	if (ret != 0) {
		perror("pthread_setaffinity_np");
		return NULL;
	}

	printf("Core 1 is running!\n");
	/* waste some time so the work is visible with "top" */
	printf("result: %f\n", waste_time(5));

	pthread_exit(NULL);
	return NULL;
}

int main(int argc, char *argv[])
{
	pthread_t my_thread;
	time_t startwtime, endwtime;

	startwtime = time(NULL);

	if (pthread_create(&my_thread, NULL, thread_func, NULL) != 0) {
		perror("pthread_create");
	}

	pthread_join(my_thread, NULL);

	endwtime = time(NULL);

	printf("wall clock time = %ld\n", (endwtime - startwtime));

	return 0;
}
