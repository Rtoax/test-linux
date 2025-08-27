#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <sys/types.h>

#include <libs/log.h>

void *thread(void *arg)
{
	size_t stacksize;
	pthread_attr_t attr;

	pthread_attr_init(&attr);
	pthread_attr_getstacksize(&attr, &stacksize);
	log_child("stacksize: %ld MB\n", stacksize / 1024 / 1024);

	return ((void *)0);
}

int main(void)
{
	pthread_t tid;
	pthread_attr_t attr;

	pthread_attr_init(&attr);

#if 1
	size_t stacksize;
	pthread_attr_setstacksize(&attr, 4096);
	pthread_attr_getstacksize(&attr, &stacksize);
	log_parent("stacksize: %ld MB\n", stacksize / 1024 / 1024);
#endif

	pthread_create(&tid, &attr, thread, NULL);

	pthread_join(tid, NULL);

	return 0;
}
