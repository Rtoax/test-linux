#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <stdlib.h>

/**
 * mutex1， mutex2分别绑定不同的线程，不能唤醒
 * 以上代码能够成功唤醒三个线程，但是如果每一个线程的条件变量绑定不同的互斥量时，
 * 每一次调用pthread_cond_brodcast时，就只能唤醒一个线程。
 * 比如以下程序，每次只能唤醒第一个绑定了互斥量的线程，其他线程均无法被唤醒。
 */
pthread_cond_t cond = PTHREAD_COND_INITIALIZER;
pthread_mutex_t mutex1 = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t mutex2 = PTHREAD_MUTEX_INITIALIZER;


void *thread_task1(void *arg)
{
	pthread_mutex_lock(&mutex1);

	pthread_cond_wait(&cond, &mutex1);

	printf("thread_task1 start working\n");
	sleep(2);
	printf("thread_task1 works over\n");
	pthread_mutex_unlock(&mutex1);

	return NULL;
}

void *thread_task2(void *arg)
{
	pthread_mutex_lock(&mutex1);

	pthread_cond_wait(&cond, &mutex1);

	printf("thread_task2 start working\n");
	sleep(2);
	printf("thread_task2 works over\n");
	pthread_mutex_unlock(&mutex1);

	return NULL;
}

void *thread_task3(void *arg)
{
	pthread_cond_broadcast(&cond);

	return NULL;
}

int main(void)
{
	pthread_t thread_1,thread_2,thread_3;
	pthread_create(&thread_1,NULL,thread_task1,NULL);
	pthread_create(&thread_2,NULL,thread_task2,NULL);

	sleep(2);

	pthread_create(&thread_3,NULL,thread_task3,NULL);

	sleep(5);

	pthread_join(thread_1,NULL);
	pthread_join(thread_2,NULL);

	return 0;
}

