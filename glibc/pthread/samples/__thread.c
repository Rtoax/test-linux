/**
 * Thread-Local Storage Access Models - TLS
 */
#include <pthread.h>
#include <stdio.h>

struct test1 {
	 int  id;
};

__thread struct test1 t;
__thread int tid = 0;

void* test_task_fn(void* unused)
{
	printf("test_task_fn.\n");

	tid++;
	t.id++;

	printf("child: tid = %d\n", tid);
	printf("child: t.id = %d\n", t.id);

	pthread_exit(NULL);
	return NULL;
}

int main ()
{
	pthread_t t1, t2;

	pthread_create(&t1, NULL, test_task_fn, NULL);
	pthread_create(&t2, NULL, test_task_fn, NULL);

	pthread_join(t1, NULL);
	pthread_join(t2, NULL);

	printf("parent: tid = %d\n", tid);
	printf("parent: t.id = %d\n", t.id);

	return 0;
}

