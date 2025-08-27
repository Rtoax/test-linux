/**
 * TSD - thread specific data
 */
#include <pthread.h>
#include <stdio.h>
#include <stdint.h>

pthread_key_t key;
pthread_t thid1;
pthread_t thid2;

void *thread2(void *arg)
{
	int key_va = 3;
	pthread_setspecific(key, &key_va);
	printf("thread:%lu return %ld\n",
	       pthread_self(), *(intptr_t *) pthread_getspecific(key));

	return NULL;
}

void *thread1(void *arg)
{
	int key_va = 5;
	pthread_setspecific(key, &key_va);
	pthread_create(&thid2, NULL, thread2, NULL);
	printf("thread:%lu return %ld\n",
	       pthread_self(), *(intptr_t *) pthread_getspecific(key));

	return NULL;
}

int main(void)
{
	printf("main thread:%lu is running\n", pthread_self());

	pthread_key_create(&key, NULL);

	pthread_create(&thid1, NULL, thread1, NULL);

	pthread_join(thid1, NULL);
	pthread_join(thid2, NULL);

	int key_va = 1;
	pthread_setspecific(key, &key_va);
	printf("thread:%lu return %ld\n",
	       pthread_self(), *(intptr_t *) pthread_getspecific(key));
	pthread_key_delete(key);

	return 0;
}
