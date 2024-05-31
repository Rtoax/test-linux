#include <pthread.h>
#include <stdio.h>

pthread_cond_t cond2;
pthread_condattr_t cond2attr;

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
	pthread_t thread_id;

	pthread_condattr_init(&cond2attr);
	pthread_condattr_setpshared(&cond2attr, PTHREAD_PROCESS_SHARED);

	pthread_cond_init(&cond2, &cond2attr);

	pthread_create(&thread_id, NULL, test_task_fn, NULL);

	pthread_join(thread_id, (void**)&pstatus);

	printf("pstatus = %d\n", *pstatus);

	pthread_cond_destroy(&cond2);
	pthread_condattr_destroy(&cond2attr);

	return 0;
}
