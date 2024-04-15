#include <stdio.h>
#include <pthread.h>
#include <emmintrin.h> // _mm_pause()


typedef struct {
	/* 1:locked 0:unlocked */
	volatile int locked;
} cus_spinlock_t;


static inline void cus_pause(void)
{
	_mm_pause();
	return;
}

void cus_spinlock_unlock(cus_spinlock_t *lock)
{
	__sync_lock_release(&lock->locked);
}

void cus_spinlock_lock(cus_spinlock_t *lock)
{
	while (__sync_lock_test_and_set(&lock->locked, 1) == 1) {
		while (lock->locked == 1) {
			cus_pause();
		}
	}
}

void cus_spinlock_init(cus_spinlock_t *lock)
{
	lock->locked = 0;
}


#define NR_NUM	50000
#define NR_THREADS	10

int sum = 0;
cus_spinlock_t spinlock;

void *test_func(void *arg)
{
	int i;
	for (i = 0; i < NR_NUM; i++) {
#ifndef NONLOCK
		cus_spinlock_lock(&spinlock);
#endif
		sum++;
#ifndef NONLOCK
		cus_spinlock_unlock(&spinlock);
#endif
	}
	pthread_exit(NULL);
}

int main(void)
{
	int i;
	pthread_t threadids[NR_THREADS];

	cus_spinlock_init(&spinlock);

#ifdef NONLOCK
	printf("Non lock.\n");
#endif

	for (i = 0; i < NR_THREADS; i++)
		pthread_create(&threadids[i], NULL, test_func, NULL);

	for (i = 0; i < NR_THREADS; i++)
		pthread_join(threadids[i], NULL);

	printf("sum = %d\n", sum);
	return 0;
}
