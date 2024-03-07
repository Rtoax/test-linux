#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>

typedef struct Struct {
	sem_t *lock;
	int num;
} STRUCT;

void test(void *obj)
{
	STRUCT *point = (STRUCT*)obj;
	sem_t *semlock = NULL;
	int j = 0;

	semlock = point->lock;
	sem_wait(semlock);

	FILE *f = fopen("test.txt", "a");

	if (f == NULL) {
		printf("fopen error\n");
		f = stderr;
	}
	printf("num %d\n", point->num);

	for (j = 0; j < 30; j++) {
		fprintf(f, "%c-", 'a' + point->num);
	}

	fprintf(f, "%c\n", 'a' + point->num);

	if (f && f != stderr)
		fclose(f);
	sem_post(semlock);
	return;
}

#define NR_THREADS	20

int main(void)
{
	pthread_t pid[NR_THREADS];

	int ret, i = 0;

	STRUCT obj[NR_THREADS];

	sem_t semlock;
	if (sem_init(&semlock, 0, 1) != 0) {
		printf("sem_init error\n");
	}
	for (i = 0; i < NR_THREADS; i++) {
		obj[i].num = i;
		obj[i].lock = &semlock;
		ret = pthread_create(&pid[i], NULL, (void *)test, &obj[i]);

		if (ret != 0) {
			printf("create thread wrong %d\n", i);
			return 0;
		}
	}
	for (i = 0; i < NR_THREADS; i++) {
		pthread_join(pid[i], NULL);
	}

	return 1;
}
