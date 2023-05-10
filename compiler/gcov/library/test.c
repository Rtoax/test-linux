#include <stdio.h>
#include <pthread.h>
#include <sys/time.h>
#include "library.h"

#define LIB_BRANCH_FN branch_f1
#include "branch.h"
#undef LIB_BRANCH_FN

struct thread_arg {
	int id;
};

__thread int threadid = 0;

void* thread_fn(void *arg)
{
	struct thread_arg *targ = arg;
	threadid = targ->id;

	branch_f1(10000000);

	lib_f1();
	printf("Thread %d.\n", threadid);

	return NULL;
}

int main(int argc, char *argv[])
{
	pthread_t t1, t2;

	struct thread_arg a1 = { .id = 1, };
	struct thread_arg a2 = { .id = 2, };

	pthread_create(&t1, NULL, thread_fn, &a1);
	pthread_create(&t2, NULL, thread_fn, &a2);

	pthread_join(t1, NULL);
	pthread_join(t2, NULL);

	printf("Done.\n");
}

