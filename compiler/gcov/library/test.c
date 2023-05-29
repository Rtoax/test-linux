#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <sys/time.h>
#include "library.h"

#define COMPILE_TEST
#define LIB_BRANCH_FN branch_f1
#include "branch.h"
#undef LIB_BRANCH_FN

struct thread_arg {
	int id;
};

pthread_key_t thread_log_key;

__thread int threadid = 0;

void thread_log_key_dtor(void *thread_log)
{
	fclose((FILE*)thread_log);
}

void log_thread(const char *message)
{
	FILE *thread_log_fp = (FILE *)pthread_getspecific(thread_log_key);
	fprintf(thread_log_fp, "%s\n", message);
}

void* thread_fn(void *arg)
{
	struct thread_arg *targ = arg;
	threadid = targ->id;

	branch_f1(10000000);

	lib_f1();

	FILE *logfp;
	char filename[64];
	sprintf(filename, "thread%d-%ld.log", threadid, pthread_self());
	logfp = fopen(filename, "w");

	pthread_setspecific(thread_log_key, logfp);

	log_thread("This is thread.");

	sort_array();

	printf("Thread %d(%ld).\n", threadid, pthread_self());

	return NULL;
}

int main(int argc, char *argv[])
{
	pthread_t t1, t2;

	struct thread_arg a1 = { .id = 1, };
	struct thread_arg a2 = { .id = 2, };

	pthread_key_create(&thread_log_key, thread_log_key_dtor);

	pthread_create(&t1, NULL, thread_fn, &a1);
	pthread_create(&t2, NULL, thread_fn, &a2);

	pthread_join(t1, NULL);
	pthread_join(t2, NULL);

	printf("Done.\n");
}

