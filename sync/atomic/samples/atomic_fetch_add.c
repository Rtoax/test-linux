/**
 * https://en.cppreference.com/w/c/atomic
 */
#include <stdio.h>
#include <pthread.h>
#include <stdatomic.h>

atomic_int acnt;
int cnt;

void *f(void *thr_data)
{
	int n;
	for (n = 0; n < 1000; ++n) {
		/**
		 * __sync_fetch_and_add(&acnt, 1);
		 */
		atomic_fetch_add_explicit(&acnt, 1, memory_order_relaxed);
		++cnt;
	}
	return 0;
}

int main(void)
{
	int n;
	pthread_t thr[10];

	for (n = 0; n < 10; ++n)
		pthread_create(&thr[n], NULL, f, NULL);
	for (n = 0; n < 10; ++n)
		pthread_join(thr[n], NULL);

	printf("The atomic counter is %u\n", acnt);
	printf("The non-atomic counter is %u\n", cnt);
	return 0;
}

