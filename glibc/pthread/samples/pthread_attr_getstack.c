#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <sys/types.h>

#include <libs/log.h>

void *thread(void *arg)
{
	void *stack;
	size_t stacksize;
	pthread_attr_t attr;

	pthread_attr_init(&attr);
	pthread_attr_getstack(&attr, &stack, &stacksize);
	log_parent("%p stacksize:%ld\n", stack, stacksize);

	return ((void *)0);
}

int main(void)
{
	void *stack;
	size_t stacksize;
	pthread_t tid;
	pthread_attr_t attr;

	pthread_attr_init(&attr);
	pthread_create(&tid, &attr, thread, NULL);

	pthread_attr_getstack(&attr, &stack, &stacksize);
	log_child("%p stacksize:%ld\n", stack, stacksize);

	pthread_join(tid, NULL);

	return 0;
}
