#include <limits.h>
#include <pthread.h>
#include <sched.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/mman.h>

void *thread_func(void *arg)
{
	while (1);
	//sleep(2);
	/* Do RT specific stuff here */
	return NULL;
}

int main(int argc, char *argv[])
{
	struct sched_param param;

	pthread_attr_t attr;
	pthread_t thread;

	int ret;

	if (mlockall(MCL_CURRENT | MCL_FUTURE)) {
		perror("mlockall failed.");
		exit(-2);
	}

	ret = pthread_attr_init(&attr);
	if (ret) {
		perror("pthread_attr_init");
		goto out;
	}
	if (pthread_attr_setstacksize(&attr, PTHREAD_STACK_MIN)) {
		perror("pthread_attr_setstacksize");
		goto out;
	}

	ret  = pthread_attr_setschedpolicy(&attr, SCHED_FIFO);
	if (ret) {
		perror("pthread_attr_setschedpolicy");
		goto out;
	}

	param.sched_priority = 80;
	ret = pthread_attr_setschedparam(&attr, &param);
	if (ret) {
		perror("pthread_attr_setschedparam");
		goto out;
	}
	ret = pthread_create(&thread, &attr, thread_func, NULL);
	if (ret) {
		perror("pthread_attr_setschedparam");
		goto out;
	}

	ret = pthread_join(thread, NULL);
	if (ret) {
		perror("pthread_join");
	}

out:
	return ret;
}
