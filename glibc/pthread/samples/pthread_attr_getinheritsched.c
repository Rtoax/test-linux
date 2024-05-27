#define __USE_GNU
#include <pthread.h>
#include <stdio.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <sched.h>

#include <libs/memshow.h>


static void print_policy(int policy)
{
	switch (policy) {
	case SCHED_FIFO: printf("SCHED_FIFO\n"); break;
	case SCHED_RR: printf("SCHED_RR\n"); break;
	case SCHED_OTHER: printf("SCHED_OTHER\n"); break;
	}
}

void *test_task_fn(void *unused)
{
	static int status = 12121;
	pthread_attr_t attr;
	int policy;

	memshow("pthread_attr_t before init ", &attr, sizeof(pthread_attr_t));

	pthread_attr_init(&attr);
	memshow("pthread_attr_t after init  ", &attr, sizeof(pthread_attr_t));

	pthread_attr_getschedpolicy(&attr, &policy);
	print_policy(policy);

	pthread_attr_setinheritsched(&attr, PTHREAD_EXPLICIT_SCHED);
	pthread_attr_setschedpolicy(&attr, SCHED_RR);

	pthread_attr_getschedpolicy(&attr, &policy);
	print_policy(policy);

	memshow("pthread_attr_t after init  ", &attr, sizeof(pthread_attr_t));

	pthread_attr_destroy(&attr);
	pthread_exit(&status);
	return NULL;
}

int main(void)
{
	int *pstatus;
	pthread_t thread_id;

	pthread_create(&thread_id, NULL, test_task_fn, NULL);

	pthread_join(thread_id, (void**)&pstatus);

	printf("pstatus = %d\n", *pstatus);
	return 0;
}
