/**
 * Thread-Local Storage Access Models - TLS
 */
#include <pthread.h>
#include <stdio.h>

struct test1 {
	int id;
};

#define __tls __attribute__((tls_model("local-exec")))

__thread __tls struct test1 t;
__thread __tls int tid = 0;

void *test_task_fn(void *unused)
{
	printf("test_task_fn.\n");

	tid++;
	t.id++;

	printf("child: tid = %d\n", tid);
	printf("child: t.id = %d\n", t.id);

	pthread_exit(NULL);
	return NULL;
}

int main(void)
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
