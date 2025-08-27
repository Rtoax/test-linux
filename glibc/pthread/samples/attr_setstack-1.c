#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <pthread.h>
#include <errno.h>

pthread_attr_t attr;

void *thread(void *arg)
{
	void *stack;
	size_t stacksize;

	printf("thread run\n");

	pthread_attr_getstack(&attr, &stack, &stacksize);
	printf("%p stacksize:%lu\n", stack, stacksize);

	return ((void *)0);
}

int main(void)
{
	pthread_t tid;
	void *stack;
	size_t stacksize = 1024;

	pthread_attr_init(&attr);
	stack = malloc(stacksize);

	pthread_attr_setstack(&attr, stack, stacksize);

	pthread_create(&tid, &attr, thread, NULL);

	pthread_join(tid, NULL);

	return 0;
}
