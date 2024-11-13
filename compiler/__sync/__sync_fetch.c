#include <stdio.h>
#include <pthread.h>
#include <stdatomic.h>

atomic_int acnt;
int cnt;

void *test__sync_fetch_and_add(void *thr_data)
{
	int n;
	for (n = 0; n < 1000; ++n) {
		__sync_fetch_and_add(&acnt, 1);
		++cnt;
	}
	return 0;
}

void *test__sync_fetch_and_sub(void *thr_data)
{
	int n;
	for (n = 0; n < 1000; ++n) {
		__sync_fetch_and_sub(&acnt, 1);
		++cnt;
	}
	return 0;
}

#define NR_THREAD 10

void exec_threads(void *(*fn)(void *), int init, int expect)
{
	int n;
	pthread_t thr[NR_THREAD];

	acnt = init;
	cnt = 0;

	for (n = 0; n < NR_THREAD; ++n)
		pthread_create(&thr[n], NULL, fn, NULL);

	for (n = 0; n < NR_THREAD; ++n)
		pthread_join(thr[n], NULL);

	printf("The atomic counter is %u\n", acnt);
	printf("The non-atomic counter is %u\n", cnt);
}

int main(void)
{
	exec_threads(test__sync_fetch_and_add, 0, 1000 * NR_THREAD);
	exec_threads(test__sync_fetch_and_sub, 1000 * NR_THREAD, 0);
	return 0;
}

