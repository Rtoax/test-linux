#include <pthread.h>
#include <stdio.h>
#include <assert.h>

#define MY_STACK_SIZE 1024*1024

static void create_rt_thread(void *(*rt_func)(void*))
{
	pthread_t thread;
	pthread_attr_t attr;

	if (pthread_attr_init(&attr)) {
		perror("pthread_attr_init");
		assert(0);
		return ;
	}
	if (pthread_attr_setstacksize(&attr, PTHREAD_STACK_MIN + MY_STACK_SIZE)) {
		perror("pthread_attr_setstacksize");
		assert(0);
		return ;
	}
	pthread_create(&thread, &attr, rt_func, NULL);
}

void* routine(void* unused)
{
	return NULL;
}

int main(void)
{
	create_rt_thread(routine);

	return 0;
}
