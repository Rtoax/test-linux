#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <malloc.h>
#include <unistd.h>
#include <stdbool.h>

#define printFoo() fprintf(stderr, "foo")
#define printBar() fprintf(stderr, "bar")

typedef struct {
	int n;
	bool flag;
	pthread_mutex_t mutex;
	pthread_cond_t cond;
} FooBar;

FooBar *fooBarCreate(int n)
{
	FooBar *obj = (FooBar *) malloc(sizeof(FooBar));
	obj->n = n;
	obj->flag = true;
	pthread_mutex_init(&obj->mutex, NULL);
	pthread_cond_init(&obj->cond, NULL);

	return obj;
}

void foo(FooBar *obj)
{
	int i;
	for (i = 0; i < obj->n; i++) {
		pthread_mutex_lock(&obj->mutex);
		while (false == obj->flag)
			pthread_cond_wait(&obj->cond, &obj->mutex);
		printFoo();
		obj->flag = false;
		pthread_cond_signal(&obj->cond);
		pthread_mutex_unlock(&obj->mutex);
	}
}

void bar(FooBar *obj)
{
	int i;
	for (i = 0; i < obj->n; i++) {
		pthread_mutex_lock(&obj->mutex);
		while (true == obj->flag)
			pthread_cond_wait(&obj->cond, &obj->mutex);
		printBar();
		obj->flag = true;
		pthread_cond_signal(&obj->cond);
		pthread_mutex_unlock(&obj->mutex);
	}
}

void fooBarFree(FooBar *obj)
{
	pthread_mutex_destroy(&obj->mutex);
	pthread_cond_destroy(&obj->cond);

	free(obj);
}

void *thread_foo(void *arg)
{
	FooBar *fb = (FooBar *) arg;
	foo(fb);
	return NULL;
}

void *thread_bar(void *arg)
{
	FooBar *fb = (FooBar *) arg;
	bar(fb);
	return NULL;
}

int main(int argc, char *argv[])
{
	FooBar *foobar = fooBarCreate(10);

	pthread_t t1, t2;

	pthread_create(&t1, NULL, thread_foo, foobar);
	pthread_create(&t2, NULL, thread_bar, foobar);

	pthread_join(t1, NULL);
	pthread_join(t2, NULL);

	fooBarFree(foobar);
}
