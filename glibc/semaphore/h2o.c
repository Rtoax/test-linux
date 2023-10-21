#define __USE_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <malloc.h>
#include <unistd.h>
#include <stdbool.h>
#include <semaphore.h>

#define releaseHydrogen() fprintf(stderr, "H")
#define releaseOxygen() fprintf(stderr, "O")

typedef struct {
	sem_t H;
	sem_t O;
	int waitcnt;
} H2O;

H2O* h2oCreate(void)
{
	H2O* obj = (H2O*) malloc(sizeof(H2O));
	sem_init(&(obj->H), 0, 2);
	sem_init(&(obj->O), 0, 1);
	obj->waitcnt = 0;
	return obj;
}

void h2oFree(H2O* obj)
{
	sem_destroy(&(obj->H));
	sem_destroy(&(obj->O));
	free(obj);
}

void hydrogen(H2O* obj)
{
	sem_wait(&(obj->H));
	releaseHydrogen();
	obj->waitcnt++;
	if (obj->waitcnt == 2) {
		sem_post(&(obj->O));
		obj->waitcnt = 0;
	}
}

void oxygen(H2O* obj)
{
	sem_wait(&(obj->O));
	releaseOxygen();
	sem_post(&(obj->H));
	sem_post(&(obj->H));
}

void *thread_hydrogen(void *arg)
{
	H2O* fb = (H2O* )arg;
	hydrogen(fb);
	return NULL;
}

void *thread_oxygen(void *arg)
{
	H2O* fb = (H2O* )arg;
	oxygen(fb);
	return NULL;
}

int main(int argc, char *argv[])
{
	H2O* h2o = h2oCreate();

	pthread_t t1, t2, t3;

	pthread_create(&t1, NULL, thread_hydrogen, h2o);
	pthread_create(&t3, NULL, thread_hydrogen, h2o);

	pthread_create(&t2, NULL, thread_oxygen, h2o);

	pthread_join(t1, NULL);
	pthread_join(t2, NULL);
	pthread_join(t3, NULL);

	h2oFree(h2o);
}