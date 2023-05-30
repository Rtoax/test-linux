#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <sys/time.h>
#include "library.h"

#define COMPILE_TEST
#define LIB_BRANCH_FN branch_f1
#include "branch.h"
#undef LIB_BRANCH_FN

#define LAYOUT_FN_TEST	test_layout_test
#define LAYOUT_FN_A		test_layout_A_
#define LAYOUT_FN_B		test_layout_B_
#define LAYOUT_FN_C		test_layout_C
#define LAYOUT_FN_D		test_layout_D_
#define LAYOUT_FN_E		test_layout_E
#define LAYOUT_FN_F		test_layout_F_
#define LAYOUT_FN_G		test_layout_G
#define LAYOUT_FN_H		test_layout_H_
#define LAYOUT_FN_I		test_layout_I
#define LAYOUT_FN_J		test_layout_J_
#include "layout.h"
#undef LAYOUT_FN_TEST
#undef LAYOUT_FN_A
#undef LAYOUT_FN_B
#undef LAYOUT_FN_C
#undef LAYOUT_FN_D
#undef LAYOUT_FN_E
#undef LAYOUT_FN_F
#undef LAYOUT_FN_G
#undef LAYOUT_FN_H
#undef LAYOUT_FN_I
#undef LAYOUT_FN_J

void test_lib()
{
#ifdef TEST_LIB
	lib_f1();
	sort_array();
	lib_layout_test();
#endif
}

struct thread_arg {
	int id;
	unsigned long ret;
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

	targ->ret = branch_f1(rand() % 10000000);
	targ->ret += test_layout_test();

	test_lib();

	FILE *logfp;
	char filename[64];
	sprintf(filename, "thread%d-%ld.log", threadid, pthread_self());
	logfp = fopen(filename, "w");

	pthread_setspecific(thread_log_key, logfp);

	log_thread("This is thread.");

	printf("Thread %d(%ld).\n", threadid, pthread_self());

	return NULL;
}

int main(int argc, char *argv[])
{
	pthread_t t1, t2;

	struct thread_arg a1 = { .id = 1, };
	struct thread_arg a2 = { .id = 2, };

	srand((int)time(0));

	pthread_key_create(&thread_log_key, thread_log_key_dtor);

	pthread_create(&t1, NULL, thread_fn, &a1);
	pthread_create(&t2, NULL, thread_fn, &a2);

	pthread_join(t1, NULL);
	pthread_join(t2, NULL);

	printf("Thread1 ret %ld\n", a1.ret);
	printf("Thread2 ret %ld\n", a2.ret);
	printf("Done.\n");
}

