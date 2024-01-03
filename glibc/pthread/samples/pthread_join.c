/**
 * 通过调用pthread_join等待一个给定线程终止，对比线程和UNIX进程,
 * pthread_create类似于fork函数，pthread_join类似于waitpid函数.
 */
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<pthread.h>
#include<string.h>

void *fun1(void *arg)
{
	printf("I'm thread 1;\n");
	return (void *)1;
}

void *fun2(void *arg)
{
	printf("I'm thread 2;\n");
	pthread_exit((void *)2);
}

void *fun3(void *arg)
{
	while (1) {
		printf("I'm thread 3;\n");
		pthread_testcancel();
	}

	return ((void *)3);
}

int main(void)
{
	pthread_t tid;
	void *retval = NULL;
	int ret;
	int err;

	ret = pthread_create(&tid, NULL, fun1, NULL);
	if (ret != 0) {
		fprintf(stderr, "pthread_create error:%s\n", strerror(ret));
	}
	err = pthread_join(tid, (void **)&retval);
	if (err != 0) {
		fprintf(stderr, "pthread_join error:%s\n", strerror(err));
	}
	printf("thread exit code :%ld\n", (intptr_t) retval);

	ret = pthread_create(&tid, NULL, fun2, NULL);
	if (ret != 0) {
		fprintf(stderr, "pthread_create error:%s\n", strerror(ret));
	}
	err = pthread_join(tid, (void **)&retval);
	if (err != 0) {
		fprintf(stderr, "pthread_join error:%s\n", strerror(err));
	}
	printf("thread exit code :%ld\n", (intptr_t) retval);

	ret = pthread_create(&tid, NULL, fun3, NULL);
	if (ret != 0) {
		fprintf(stderr, "pthread_create error:%s\n", strerror(ret));
	}

	sleep(2);
	pthread_cancel(tid);
	err = pthread_join(tid, (void **)&retval);
	if (err != 0) {
		fprintf(stderr, "pthread_join error:%s\n", strerror(err));
	}
	printf("thread exit code :%ld\n", (intptr_t) retval);

	return 0;
}
