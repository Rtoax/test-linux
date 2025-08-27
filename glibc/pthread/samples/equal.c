#include <pthread.h>
#include <stdio.h>

#include <libs/log.h>

void *test_task_fn(void *unused)
{
	pthread_t threadid;
	int ret;

	threadid = pthread_self();

	ret = pthread_equal(pthread_self(), threadid);
	if (ret) {
		log_child("equal.\n");
	}

	pthread_exit(&threadid);
	return NULL;
}

int main(void)
{
	int eret;
	pthread_t thread_id;
	pthread_t *threadid_child;

	pthread_create(&thread_id, NULL, test_task_fn, NULL);

	pthread_join(thread_id, (void **)&threadid_child);

	eret = pthread_equal(pthread_self(), *threadid_child);
	if (eret == 0) {
		log_parent("non-equal.\n");
	}

	return 0;
}
