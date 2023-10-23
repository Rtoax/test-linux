#include <pthread.h>
#include <stdio.h>

#include <libs/log.h>


pthread_spinlock_t spinlock;


void* test_task_fn(void* unused)
{
	pthread_spin_lock(&spinlock);

	log_child("test_task_fn %ld.\n", pthread_self());

	pthread_spin_unlock(&spinlock);

	pthread_exit(NULL);

	return NULL;
}

int main(void)
{
	int *pstatus;
	pthread_t thread_id1, thread_id2;

	pthread_spin_init(&spinlock, PTHREAD_PROCESS_SHARED);

	pthread_create(&thread_id1, NULL, test_task_fn, NULL);
	pthread_create(&thread_id2, NULL, test_task_fn, NULL);

	pthread_join(thread_id1, (void**)&pstatus);
	pthread_join(thread_id2, (void**)&pstatus);

	pthread_spin_destroy(&spinlock);

	return 0;
}



