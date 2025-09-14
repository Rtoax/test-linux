#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <semaphore.h>
#include <pthread.h>
#include <unistd.h>

int num = 0;
sem_t sem1, sem2;

void *t_read(void *arg)
{
	int i;
	int arr[5] = {1, 2, 3, 4, 5};

	for (i = 0; i < 5; i++) {
		sem_wait(&sem1);
		num = arr[i];
		sem_post(&sem2);
	}
	return 0;
}

void *t_accu(void *arg)
{
	int i, sum = 0;
	for (i = 0; i < 5; i++) {
		sem_wait(&sem2);
		sum += num;
		sem_post(&sem1);
	}
	printf("sum: %d \n", sum);
	return 0;
}

int main(void)
{
	pthread_t t_id[2];

	sem_init(&sem1, 0, 1);
	sem_init(&sem2, 0, 0);

	pthread_create(&t_id[0], NULL, t_read, NULL);
	pthread_create(&t_id[1], NULL, t_accu, NULL);

	pthread_join(t_id[0], NULL);
	pthread_join(t_id[1], NULL);

	sem_destroy(&sem1);
	sem_destroy(&sem2);
	return 0;
}
