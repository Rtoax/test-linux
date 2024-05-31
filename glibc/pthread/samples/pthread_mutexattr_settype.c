#include <pthread.h>
#include <stdio.h>

pthread_mutex_t mutex;
pthread_mutexattr_t mutexattr;

void recursive_test(const char *hint, int count)
{
	pthread_mutex_lock(&mutex);

	printf("%s >> %d\n", hint, count);
	if (count > 1)
		recursive_test(hint, count - 1);

	pthread_mutex_unlock(&mutex);
}

void *test_task1_fn(void *unused)
{
	printf("test_task1_fn.\n");

	recursive_test("T1", 3);

	pthread_exit(NULL);
	return NULL;
}

void *test_task2_fn(void *unused)
{
	printf("test_task2_fn.\n");

	recursive_test("T2", 3);

	pthread_exit(NULL);
	return NULL;
}

int main(void)
{
	int *pstatus, mutextype;
	pthread_t thread_id1, thread_id2;

	pthread_mutexattr_init(&mutexattr);

	/**
	 * deprecated mutex creation attributes:
	 * - pthread_mutexattr_setkind_np()
	 * - pthread_mutexattr_getkind_np()
	 *
	 * kind:
	 * - PTHREAD_MUTEX_FAST_NP
	 * - PTHREAD_MUTEX_RECURSIVE_NP
	 * - PTHREAD_MUTEX_ERRORCHECK_NP
	 */
	pthread_mutexattr_settype(&mutexattr, PTHREAD_MUTEX_RECURSIVE);
	pthread_mutexattr_gettype(&mutexattr, &mutextype);

	printf("mutextype = %x\n", mutextype);

	pthread_mutex_init(&mutex, &mutexattr);

	pthread_create(&thread_id1, NULL, test_task1_fn, NULL);
	pthread_create(&thread_id2, NULL, test_task2_fn, NULL);

	pthread_join(thread_id1, (void **)&pstatus);
	pthread_join(thread_id1, (void **)&pstatus);

	pthread_mutex_destroy(&mutex);
	return 0;
}
