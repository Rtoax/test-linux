/**
 * Thread-Local Storage Access Models - TLS
 */
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

#define NR_THREADS	10

struct test1 {
	int id;
};

#define __tls __attribute__((tls_model("local-exec")))

__thread __tls struct test1 t;
__thread __tls int tid = 0;

void *test_task_fn(void *unused)
{
	int r;
	printf("test_task_fn.\n");

	r = (int)(10.0 * rand() / RAND_MAX + 1.0);

	tid = r;
	t.id = r;

	printf("child: tid = %d, t.id = %d\n", tid, t.id);

	pthread_exit(NULL);
	return NULL;
}

int main(void)
{
	int i;
	pthread_t threads[NR_THREADS];

	for (i = 0; i < NR_THREADS; i++)
		pthread_create(&threads[i], NULL, test_task_fn, NULL);

	for (i = 0; i < NR_THREADS; i++)
		pthread_join(threads[i], NULL);

	printf("parent: tid = %d\n", tid);
	printf("parent: t.id = %d\n", t.id);

	return 0;
}
