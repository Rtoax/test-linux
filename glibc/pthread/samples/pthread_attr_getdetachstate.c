#include <pthread.h>
#include <stdio.h>
#include <stdio.h>

#include <libs/memshow.h>


void *test_task_fn(void *unused)
{
	printf("test_task_fn.\n");
	static int status = 12121;
	pthread_attr_t attr;
	int detachstate;

	memshow("pthread_attr_t before init ", &attr, sizeof(pthread_attr_t));

	pthread_attr_init(&attr);
	memshow("pthread_attr_t after init  ", &attr, sizeof(pthread_attr_t));

	pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED);
	memshow("pthread_attr_t after detach", &attr, sizeof(pthread_attr_t));

	pthread_attr_getdetachstate(&attr, &detachstate);

	printf("detachstate = %d.\n", detachstate); //PTHREAD_CREATE_DETACHED==1

	pthread_attr_destroy(&attr);
	pthread_exit(&status);
	return NULL;
}

int main(void)
{
	int *pstatus;
	pthread_t thread_id;

	pthread_create(&thread_id, NULL, test_task_fn, NULL);

	pthread_join(thread_id, (void**)&pstatus);

	printf("pstatus = %d\n", *pstatus);
	return 0;
}
