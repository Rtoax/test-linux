#include <pthread.h>
#include <stdio.h>

pthread_cond_t cond2;
pthread_condattr_t cond2attr;


void print_clockid(clockid_t clockid)
{
	switch (clockid) {
	/* Identifier for system-wide realtime clock.  */
	case CLOCK_REALTIME:
		printf("Identifier for system-wide realtime clock.\n");
		break;
	/* Monotonic system-wide clock.  */
	case CLOCK_MONOTONIC:
		printf("Monotonic system-wide clock.\n");
		break;
	/* High-resolution timer from the CPU.  */
	case CLOCK_PROCESS_CPUTIME_ID:
		printf("High-resolution timer from the CPU.\n");
		break;
	/* Thread-specific CPU-time clock.  */
	case CLOCK_THREAD_CPUTIME_ID:
		printf("Thread-specific CPU-time clock.\n");
		break;
	default:
		printf("Unknown clock.\n");
		break;
	}
}

void *test_task_fn(void *unused)
{
	printf("test_task_fn.\n");

	static int status = 12121;

	pthread_exit(&status);
	return NULL;
}

int main(void)
{
	int *pstatus;
	clockid_t clockid = -1;
	pthread_t thread_id;

	pthread_condattr_init(&cond2attr);
	pthread_condattr_getclock(&cond2attr, &clockid);
	print_clockid(clockid);

	pthread_condattr_setclock(&cond2attr, CLOCK_MONOTONIC);
	pthread_condattr_getclock(&cond2attr, &clockid);
	print_clockid(clockid);

	pthread_cond_init(&cond2, &cond2attr);

	pthread_create(&thread_id, NULL, test_task_fn, NULL);

	pthread_join(thread_id, (void**)&pstatus);

	printf("pstatus = %d\n", *pstatus);

	pthread_cond_destroy(&cond2);
	pthread_condattr_destroy(&cond2attr);

	return 0;
}

