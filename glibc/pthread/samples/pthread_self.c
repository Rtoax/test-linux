#include <pthread.h>
#include <stdio.h>

#if defined(__loogarch64__)
# define builtin_thread_self() (pthread_t)__builtin_thread_pointer()
#else
# define builtin_thread_self() pthread_self()
#endif

void *test_task_fn(void *unused)
{
	static int status = 12121;

	printf(">>pthread_self() = %ld\n", pthread_self());
	printf(">>builtin_thread_self() = %ld\n", builtin_thread_self());

	pthread_exit(&status);

	return NULL;
}

int main(void)
{
	int *pstatus;
	pthread_t thread_id;

	printf("pthread_self() = %ld\n", pthread_self());
	printf(">>builtin_thread_self() = %ld\n", builtin_thread_self());

	pthread_create(&thread_id, NULL, test_task_fn, NULL);

	pthread_join(thread_id, (void **)&pstatus);

	return 0;
}
