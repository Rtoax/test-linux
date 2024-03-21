#include <pthread.h>
#include <stdio.h>

#define nr_threads  100

pthread_rwlock_t rwlock2;
int sum_count = 0;


void *test_task_write_fn(void *unused)
{
	pthread_rwlock_wrlock(&rwlock2);
	sum_count = sum_count + 1;
	pthread_rwlock_unlock(&rwlock2);
	pthread_exit(NULL);
	return NULL;
}

void *test_task_read_fn(void *unused)
{
	pthread_rwlock_rdlock(&rwlock2);
	printf("sum_count = %d\n", sum_count);
	pthread_rwlock_unlock(&rwlock2);
	pthread_exit(NULL);
	return NULL;
}

int main(void)
{
	int *pstatus;
	int i;
	pthread_t wr_threads[nr_threads];
	pthread_t rd_threads[nr_threads];

	pthread_rwlock_init(&rwlock2, NULL);

	for (i = 0; i < nr_threads; i++) {
		pthread_create(&wr_threads[i], NULL, test_task_write_fn, NULL);
		pthread_create(&rd_threads[i], NULL, test_task_read_fn, NULL);
	}

	for (i = 0; i < nr_threads; i++) {
		pthread_join(wr_threads[i], (void **)&pstatus);
		pthread_join(rd_threads[i], (void **)&pstatus);
	}

	printf("Finally sum_count = %d\n", sum_count);

	pthread_rwlock_destroy(&rwlock2);

	return 0;
}
