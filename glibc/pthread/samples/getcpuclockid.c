#include <pthread.h>
#include <stdio.h>
#include <time.h>
#include <unistd.h>

pthread_cond_t cond2;
pthread_condattr_t cond2attr;

#define test(clk_id) do { \
	printf("%s:%d\n", #clk_id, clk_id);\
} while (0)

static void print_clock(char *msg, clockid_t cid)
{
	struct timespec ts;

	printf("%s", msg);
	if (clock_gettime(cid, &ts) == -1)
		fprintf(stderr, "clock_gettime");
	printf("%4ld.%03ld\n", ts.tv_sec, ts.tv_nsec / 1000000);
}

void *test_task_fn(void *unused)
{
	static int status = 12121;
	printf("test_task_fn.\n");
	sleep(2);
#if 0 /* TODO: don't know why */
	for (;;)
		continue;
#endif
	pthread_exit(&status);
	return NULL;
}

int main(void)
{
	int *pstatus;
	clockid_t clockid = 0;
	pthread_t thread_id;

	pthread_create(&thread_id, NULL, test_task_fn, NULL);

	printf("Main thread sleeping\n");
	sleep(1);

	pthread_getcpuclockid(thread_id, &clockid);
	print_clock("  Child", clockid);

	pthread_getcpuclockid(pthread_self(), &clockid);
	print_clock(" Parent", clockid);
	print_clock("Process", CLOCK_PROCESS_CPUTIME_ID);

	pthread_join(thread_id, (void**)&pstatus);

	printf("pstatus = %d\n", *pstatus);
	return 0;
}
